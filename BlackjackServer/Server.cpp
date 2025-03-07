#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <mutex>

using namespace boost::asio;
using ip::tcp;

const int MAX_PLAYERS = 5;
std::vector<std::shared_ptr<tcp::socket>> clients;
std::mutex clients_mutex;

void handle_client(std::shared_ptr<tcp::socket> client_socket)
{
    try
    {
        while (true)
        {
            char data[1024];
            boost::system::error_code error;
            size_t length = client_socket->read_some(buffer(data), error);
            if (error == boost::asio::error::eof)
            {
                std::cout << "Client disconnected." << std::endl;
                break;
            }
            else if (error)
            {
                throw boost::system::system_error(error);
            }

            std::string received_message(data, length);
            std::cout << "Received: " << received_message << std::endl;

            // Broadcast message to all clients
            std::lock_guard<std::mutex> lock(clients_mutex);
            for (auto &client : clients)
            {
                boost::asio::write(*client, buffer(received_message));
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main()
{
    try
    {
        io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 12345));

        std::cout << "Server is running on port 12345..." << std::endl;

        while (clients.size() < MAX_PLAYERS)
        {
            auto client_socket = std::make_shared<tcp::socket>(io_service);
            acceptor.accept(*client_socket);

            {
                std::lock_guard<std::mutex> lock(clients_mutex);
                clients.push_back(client_socket);
            }

            std::cout << "New player connected! Total players: " << clients.size() << std::endl;

            std::thread(handle_client, client_socket).detach();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
