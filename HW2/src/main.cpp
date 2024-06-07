
#include <iostream>
#include <gtest/gtest.h>
#include "client.h"
#include "server.h"

void  show_pending_transactions()
{
    std::cout  <<  std::string(20, '*') <<  std::endl;
    for(const  auto& trx : pending_trxs)
    std::cout << trx <<  std::endl;
    std::cout  <<  std::string(20, '*') <<  std::endl;
}

void  show_wallets(const  Server& server)
{
    std::cout << std::string(20, '*') << std::endl;
    for(const auto& client: server.clients)
    std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}



int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        Server server{};
        auto bryan1{server.add_client("bryan")};
        auto bryan2{server.add_client("bryan")};
        auto bryan3{server.add_client("bryan")};
        std::cout<<bryan1->get_id()<<'\n'<<bryan2->get_id()<<'\n'<<bryan3->get_id()<<'\n';
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}