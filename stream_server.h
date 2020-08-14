/* Copyright (C) 2020 Oxan van Leeuwen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "esphome/core/component.h"

#include <memory>
#include <string>
#include <vector>
#include <Stream.h>
#include <ESPAsyncTCP.h>

class StreamServerComponent : public esphome::Component {
public:
    explicit StreamServerComponent(Stream *stream) : stream_{stream} {}

    void setup() override;
    void loop() override;
    void dump_config() override;
    void on_shutdown() override;

    void set_port(uint16_t port) { this->port_ = port; }

protected:
    void cleanup();
    void read();
    void write();

    struct Client {
        Client(AsyncClient *client, std::vector<uint8_t> &recv_buf);
        ~Client();

        AsyncClient *tcp_client{nullptr};
        std::string identifier{};
        bool disconnected{false};
    };

    Stream *stream_{nullptr};
    AsyncServer server_{0};
    uint16_t port_{6638};
    std::vector<uint8_t> recv_buf_{};
    std::vector<std::unique_ptr<Client>> clients_{};
};
