/*
 * Copyright © 2013-2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#include "event/mousekey/network/base_socket_messenger.h"
#include "event/mousekey/common/variable_length_array.h"
#include "socket_helper.h"
#include <boost/throw_exception.hpp>
#include <errno.h>
#include <string.h>
#include <stdexcept>
#include <QDebug>
#include <syslog.h>

namespace bs = boost::system;
namespace ba = boost::asio;

namespace {
/// Buffers need to be big enough to support messages
unsigned int const serialization_buffer_size = 2048;
}

namespace kmre {
namespace network {
template <typename stream_protocol>
BaseSocketMessenger<stream_protocol>::BaseSocketMessenger() {}

template <typename stream_protocol>
BaseSocketMessenger<stream_protocol>::BaseSocketMessenger(
    std::shared_ptr<ba::basic_stream_socket<stream_protocol>> const& socket) {
  setup(socket);
}

template <typename stream_protocol>
BaseSocketMessenger<stream_protocol>::~BaseSocketMessenger() {}

template <typename stream_protocol>
void BaseSocketMessenger<stream_protocol>::setup(
    std::shared_ptr<ba::basic_stream_socket<stream_protocol>> const& s) {
  socket = s;
  socket_fd = kmre::Fd{IntOwnedFd{socket->native_handle()}};
  socket->non_blocking(true);
  boost::asio::socket_base::send_buffer_size option(64 * 1024);
  socket->set_option(option);

  setSocketCloexec(socket->native_handle());
}

template <typename stream_protocol>
ssize_t BaseSocketMessenger<stream_protocol>::send_raw(char const* data,
                                                       size_t length) {
  VariableLengthArray<serialization_buffer_size> whole_message{length};
  std::copy(data, data + length, whole_message.data());

  std::unique_lock<std::mutex> lg(message_lock);
  return ::send(socket_fd, data, length, MSG_NOSIGNAL);
}

template <typename stream_protocol>
void BaseSocketMessenger<stream_protocol>::send(char const* data,
                                                size_t length) {
  VariableLengthArray<serialization_buffer_size> whole_message{length};
  std::copy(data, data + length, whole_message.data());

  for (;;) {
    try {
      std::unique_lock<std::mutex> lg(message_lock);
      ba::write(*socket, ba::buffer(whole_message.data(), whole_message.size()),
                boost::asio::transfer_all());
    } catch (const boost::system::system_error& err) {
      if (err.code() == boost::asio::error::try_again) {
          continue;
      }
//      throw;
    }
    break;
  }
}

template <typename stream_protocol>
void BaseSocketMessenger<stream_protocol>::async_receive_msg(
    KmreReadHandler const& handler, ba::mutable_buffers_1 const& buffer) {
  socket->async_read_some(buffer, handler);
}

template <typename stream_protocol>
bs::error_code BaseSocketMessenger<stream_protocol>::receive_msg(
    ba::mutable_buffers_1 const& buffer) {
  bs::error_code e;
  size_t nread = 0;

  while (nread < ba::buffer_size(buffer)) {
    nread +=
        boost::asio::read(*socket, ba::mutable_buffers_1{buffer + nread}, e);

    if (e && e != ba::error::would_block) break;
  }

  return e;
}

template <typename stream_protocol>
size_t BaseSocketMessenger<stream_protocol>::available_bytes() {
  boost::asio::socket_base::bytes_readable command{true};
  socket->io_control(command);
  return command.get();
}

template <typename stream_protocol>
void BaseSocketMessenger<stream_protocol>::close() {
  socket->close();
}

template class BaseSocketMessenger<boost::asio::local::stream_protocol>;
template class BaseSocketMessenger<boost::asio::ip::tcp>;
}  // namespace network
}  // namespace kmre
