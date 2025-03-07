#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;

int main()
{
    try
    {
        io_service io_service;
        tcp::socket socket(io_service);
        socket.connect(tcp::endpoint(ip::address::from_string("192.168.234.25"), 12345));

        std::cout << "Connected to Blackjack server!" << std::endl;

        std::string message;
        while (true)
        {
            std::cout << "Enter action (bet, hit, stand): ";
            std::getline(std::cin, message);

            if (message.empty())
                continue;

            boost::asio::write(socket, buffer(message));

            char data[1024];
            boost::system::error_code error;
            size_t length = socket.read_some(buffer(data), error);
            if (error == boost::asio::error::eof)
                break;
            else if (error)
                throw boost::system::system_error(error);

            std::cout << "Server response: " << std::string(data, length) << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
