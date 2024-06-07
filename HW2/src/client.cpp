#include "client.h"
#include "server.h"
#include <ctime>
#include <random>

static std::default_random_engine e(time(0));
static std::uniform_int_distribution t(0, 10000);


Client::Client(std::string id, const Server& server) : id(id) , server(&server)
{
    crypto::generate_key(public_key , private_key);
}

std::string Client::get_id()
{
    return id;
}

std::string Client::get_publickey() const
{
    return public_key;
}


double Client::get_wallet()
{
    return server->get_wallet(id);
}

std::string Client::sign(std::string txt) const
{
    std::string signature = crypto::signMessage(private_key , txt);
    return signature;
}

bool Client::transfer_money(std::string receiver, double value)
{
    double myMoney = get_wallet();
    if(myMoney < value)
    {
        return false;
    }
    if(!server->get_client(receiver))
    {
        return false;
    }
    std::string trx = id + "-" + receiver + "-" + std::to_string(value);
    std::string signature = crypto::signMessage(private_key , trx);
    server -> add_pending_trx(trx , signature);
    return true;
}

size_t Client::generate_nonce()
{
    return t(e);
}


