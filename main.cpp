#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <boost/functional/hash.hpp>
using namespace std;

// Transacton Data
struct TransactionData{
double amount;
string senderKey;
string receiverKey;
time_t timestamp;
};


// Block Class
class Block{
private:
    int index;
    size_t blockHash;
    size_t previousHash;
    size_t generateHash();

    public:
        Block(int idx,TransactionData d,size_t prevHash);

        // Get Original Hash
        size_t getHash();

        // Get previous Hash
        size_t getPreviousHash();

        //Transaction data
        TransactionData data;

        // validate hash
        bool isHashValid();
};
//constructor with params

Block::Block(int idx ,TransactionData d,size_t prevHash)
{
    index=idx;
    data=d;
    previousHash=prevHash;
    blockHash=generateHash();

}

//private functions
size_t Block::generateHash()
{


    hash<string> hash1;
    hash<size_t> hash2;
   hash<size_t> finalHash;
    string toHash = to_string(data.amount)+ data.receiverKey + data.senderKey + to_string(data.timestamp);
    return finalHash(hash1(toHash) +hash2(previousHash));

};


// Public Func
size_t Block::getHash()
{
    return blockHash;
}

size_t Block::getPreviousHash()
{
 return previousHash;
}

bool Block::isHashValid()
{
  return generateHash()  == blockHash;

}


//   Blockchain
class Blockchain{
private:
    Block createGenesisBlock();

public:
    // Public chain
    vector<Block>chain;

   //constructor

   Blockchain();

   //public functions
   void addBlock(TransactionData data);
   bool ischainValid();

   //Demo example
   Block *getLatestBlock();

};


//Blockchain constructor
Blockchain:: Blockchain()
{
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
}

Block Blockchain:: createGenesisBlock()
{

    time_t current;
    TransactionData d;
    d.amount=0;
    d.receiverKey = "None";
    d.senderKey = "None";
    d.timestamp=time(&current);


   hash<int> hash1;
    Block genesis(0,d,hash1(0));
    return genesis;
}

//Bad block for demo!!!!!!
Block *Blockchain::getLatestBlock(){
return &chain.back();
}

void Blockchain::addBlock(TransactionData d)
{

    int index=(int)chain.size()-1;
    Block newBlock(index,d,getLatestBlock()->getHash());
}

bool Blockchain::ischainValid()
{

    vector<Block>::iterator it;
    int chainLen=(int)chain.size();

    for(it=chain.begin();it!=chain.end();it++)
        {

            Block currentBlock= *it;
            if(!currentBlock.isHashValid())
            return false;

            if(chainLen >1)
            {
             Block previousBlock=*(it-1);
             if(currentBlock.getPreviousHash()!=previousBlock.getHash())
               return false;
            }

        }

        return true;
    }





int main()
{
    // Start Blockchain

    Blockchain Supercoin;

    //data for first added block
    TransactionData data1;
    time_t data1Time;
    data1.amount=1.5555;
    data1.receiverKey= "Vakul";
    data1.senderKey = "Nitin";
    data1.timestamp=time(&data1Time);

    Supercoin.addBlock(data1);
    cout<<"Is chain Valid ??"<<"\n"
    <<Supercoin.ischainValid()<<"\n";

   return 0;
}
