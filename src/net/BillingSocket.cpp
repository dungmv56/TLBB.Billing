#include "billing/net/BillingSocket.hpp"

#include "billing/Config.hpp"
#include "billing/net/Session.hpp"
#include "billing/net/Packet.hpp"

#include <iostream>

namespace net
{
  BillingSocket::BillingSocket()
  {
    std::cout << "BillingSocket is initializing..." << std::endl;

    auto configData = Config::getInstance().getData();

    // Construct asio socket
    m_acceptor = new asio::ip::tcp::acceptor(
      m_asioIoService,
      asio::ip::tcp::endpoint(
        asio::ip::address::from_string(configData->ip),
        configData->port
        )
      );

    std::cout << "BillingSocket is initialized!" << std::endl;
  }

  BillingSocket::~BillingSocket()
  {
    std::cout << "BillingSocket is destructing..." << std::endl;

    delete m_acceptor;

    std::cout << "BillingSocket is destructed!" << std::endl;
  }

  void BillingSocket::start()
  {
    std::cout << "BillingSocket is starting..." << std::endl;

    auto configData = Config::getInstance().getData();
    std::cout << "!!! BillingSocket.Acceptor will be listened at "
    << configData->ip << ":" << configData->port
    << " !!!"
    << std::endl;

    this->accept();

    m_asioIoService.run();

    std::cout << "BillingSocket is started!" << std::endl;
  }

  void BillingSocket::accept()
  {
    static asio::ip::tcp::socket m_socket(m_asioIoService);

    m_acceptor->async_accept(
      m_socket,
      [this](const std::error_code ec)
      {
        std::cout << "New connection error code: " << ec << std::endl;

        if (!ec)
        {
          Session m_session(std::move(m_socket));
        }

        this->accept();
      }
      );
  }

  void BillingSocket::stop()
  {
    std::cout << "BillingSocket is stopping..." << std::endl;

    m_asioIoService.stop();

    std::cout << "BillingSocket is stopped!" << std::endl;
  }
}

