/**********************************************************************************************************************
 * Bukhtagram                                                                                                         *
 *                                                                                                                    *
 * Author: Bukhta Mykyta                                                                                              *
 *                                                                                                                    *
 * Copyright ©2023 Bukhta Mykyta                                                                                      *
 *                                                                                                                    *
 * This software is distributed under the following license:                                                          *
 *                                                                                                                    *
 * 1. This code may not be modified, redistributed, or used to create derivative works.                               *
 * 2. Any use of this code for commercial purposes is prohibited without prior written permission of the author.      *
 * 3. The author is not liable for any damages caused by the use of this software.                                    *
 * 4. Copies of this license or references to it must be included in all copies or significant parts of the software. *
 *                                                                                                                    *
 * For permission for commercial use, contact the author at the following address: nikita.bukhta.dev@gmail.com.       *
 **********************************************************************************************************************                                                                                                                    *
 */

#include "ClientModel.hpp"
#include "ClientController.hpp"
#include "ClientView.hpp"

#include <iostream>
#include <memory>

int main(int argc, char **argv) {
    using namespace bukhtagram::mc::client;
    auto io_context = std::make_shared<boost::asio::io_context>();
    bukhtagram::mc::client::views::ClientView client_view(io_context);

    client_view.run("127.0.0.1", 12345);
    io_context->run();
    
    return 0;
}