#include "ClientView.hpp"
#include "Logger.hpp"

#include <string>
#include <iostream>
#include <thread>

namespace bukhtagram {
namespace mc {
namespace client {
namespace views {

ClientView::ClientView(std::weak_ptr<boost::asio::io_context> io_context_weak) {
    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";
    auto io_context = io_context_weak.lock();

    m_client_model = std::make_shared<models::ClientModel>(io_context);
    m_client_controller = std::make_shared<controllers::ClientController>(m_client_model);
}

bool ClientView::run(const std::string &address, uint16_t port) {
    DECLARE_TAG_SCOPE;
    LOG_INFO << "address: " << address << "; port: " << port;

    if (!m_client_controller->connect_to(address, port)) {
        LOG_ERROR << "failed to connect!";
        return false;
    }

    m_client_controller->run();

    std::thread(&ClientView::start_reading_signals, this).detach();

    return true;
};

void ClientView::start_reading_signals(void) {
    DECLARE_TAG_SCOPE;
    LOG_INFO << "called";
    // TODO: implement this logic:
    // socket->async_read_some(bufer, [buffer](error, len){ handle_signal });
    // in handle signal should be switch...case with method name:
    // switch(method) {
    // case "send_messange":
    //     send_message(args...);
    // };

    // temp logic to read message to send:

    std::istringstream input_manager;
    std::string message;
    std::getline(std::cin, message);

    std::thread(&ClientView::send_message, this, std::ref(message)).detach();
    start_reading_signals();
}

void ClientView::send_message(const std::string &message) {
    DECLARE_TAG_SCOPE;
    LOG_INFO << "message: " << message;
    m_client_controller->send_message(message);
}

}   // !views;
}   // !client;
}   // !mc;
}   // !bukhtagram;