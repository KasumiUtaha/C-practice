
#include "server.h"
#include "client.h"
#include <iostream>
#include <random>
#include <ctime>

std::vector<std::string> pending_trxs;
static std::default_random_engine e(time(0));
static std::uniform_int_distribution t(0, 9);



std::string GetRandomNumber()
{ 
    std::string s1 = std::to_string(t(e));
    std::string s2 = std::to_string(t(e));
    std::string s3 = std::to_string(t(e));
    std::string s4 = std::to_string(t(e));
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

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    for (auto &x : clients)
    {
        if (id == x.first->get_id())
        {
            return x.first;
        }
    }
    return nullptr;
}

double Server::get_wallet(std::string id) const
{
    for (auto &x : clients)
    {
        if (id == x.first->get_id())
        {
            return x.second;
        }
    }
    return 0;
}

bool Server::parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value)
{
    std::string delimiter = "-";
    for (int i = 1; i <= 3; i++)
    {
        auto pos = trx.find(delimiter);
        if (pos == std::string::npos)
        {
            if (i != 3)
            {
                throw std::runtime_error("Wrong Format");
            }
            else
            {
                pos = trx.size();
            }
        }
        std::string token = trx.substr(0, pos);
        if (i == 1)
        {
            sender = token;
        }
        else if (i == 2)
        {
            receiver = token;
        }
        else
        {
            try
            {
                value = std::stod(token);
            }
            catch (const std::exception &e)
            {
                throw std::runtime_error("Wrong Value");
            }
        }
        trx.erase(0, pos + 1);
    }
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    std::string sender, receiver;
    double value;
    parse_trx(trx, sender, receiver, value);
    if (!get_client(sender) || !get_client(receiver))
    {
        return false;
    }
    double senderMoney = get_wallet(sender);
    if (senderMoney < value)
    {
        return false;
    }
    bool authentic = crypto::verifySignature(get_client(sender)->get_publickey(), trx, signature);
    if (!authentic)
    {
        return false;
    }
    pending_trxs.push_back(trx);
    return true;
}

void Server::do_pending_trx()
{
    for (auto &trx : pending_trxs)
    {
        std::string sender, receiver;
        double value;
        parse_trx(trx, sender, receiver, value);
        std::shared_ptr<Client> senderPtr = get_client(sender);
        std::shared_ptr<Client> receiverPtr  = get_client(receiver);
        clients[senderPtr] -= value;
        clients[receiverPtr] += value;
    }
    pending_trxs.clear();
}

size_t Server::mine() 
{
    std::string mempool;
    for (auto str : pending_trxs)
    {
        mempool += str;
    }
    while (true)
    {
        for (auto &client : clients)
        {
            size_t nonce = client.first->generate_nonce();
            std::string finalString = mempool + std::to_string(nonce);
            std::string hash{crypto::sha256(finalString)};
            if (hash.substr(0, 10).find("000") != std::string::npos)
            {
                clients[client.first] += 6.25;
                do_pending_trx();
                std::cout<<"miner: "<<(client.first->get_id())<<'\n';
                return nonce;
            }
        }
    }
}
