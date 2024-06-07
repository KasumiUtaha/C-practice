
#include "server.h"
#include "client.h"
#include <random>
#include <ctime>

std::string GetRandomNumber()
{
    std::default_random_engine e(time(0));
    std::uniform_int_distribution t(0, 9);
    char s1 = t(e);
    char s2 = t(e);
    char s3 = t(e);
    char s4 = t(e);
    std::string num;
    num = num + s1 + s2 + s3 + s4;
    return num;
}

Server::Server()
{
    pending_trxs.clear();
}

std::shared_ptr<Client> Server::add_client(std::string id)
{
    for (auto &x : clients)
    {
        if (id == x.first->get_id())
        {
            id = id + GetRandomNumber();
        }
    }
    std::shared_ptr<Client> client = std::make_shared<Client>(id, *this);
    clients[client] = 5.0;
    return client;
}

std::shared_ptr<Client> Server::get_client(std::string id)
{
    for(auto& x: clients)
    {
        if(id == x.first -> get_id())
        {
            return x.first;
        }
    }
    return nullptr;
}

double Server::get_wallet(std::string id)
{
    for(auto& x:clients)
    {
        if(id == x.first->get_id())
        {
            return x.second;
        }
    }
    return 0;
}

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value)
{
    std::string delimiter = "-";
    for(int i=1;i<=3;i++)
    {
        auto pos = trx.find(delimiter);
        if(pos == std::string::npos)
        {
            if(i!=3)
            {
                throw std::runtime_error("Wrong Format");
            }
            else
            {
                pos = trx.size();
            }
        }
        std::string token =trx.substr(0,pos);
        if(i==1)
        {
            sender = token;
        } 
        else if(i==2)
        {
            receiver = token;
        }
        else
        {
            try
            {
                value = std::stod(token);
            }
            catch(const std::exception& e)
            {
                throw std::runtime_error("Wrong Value");
            }
        }
        trx.erase(0,pos+1);
    }
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature)
{
    
}



