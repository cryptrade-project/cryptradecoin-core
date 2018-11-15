// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The CryptradeCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000007270501d1029bb3661884afd701194f06a134455a28bfc5ef294b7ae862"))
    (1, uint256("0x000003df43feac069716d119fe7c725657f62bf7e2e9dd587f12521cdcbd226e"))
    (10, uint256("0x00000b2f3a1933cca0d31234c01babcedfcc0d44edc7961851c934e62ca0ae21"))
    (20, uint256("0x00000de53d19cee85ac66534a9d7156bcc477879ffaeddff633edcbae48a1553"))
    (30, uint256("0x0000029d0d6afddcb1b12c44bfb8942e6374558b93e512fa91783fab14fc47dd"))
    (40, uint256("0x00000b555f8d7e0b3addcd178609a749e24c7a64f3278d03ecaa00ccab872cdf"))
    (50, uint256("0x0000070bd916a30988e85e8fd765bf126d8a3332c08c06f8d62ef1f392246545"))
    (60, uint256("0x00000a2045fd8148669299397019cffc551348f4720959299063dd68f9110789"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1542246977, // * UNIX timestamp of last checkpoint block
    61,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    3000        // * estimated number of transactions per day after checkpoint
};

// Testnet Checkpoints
static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x0000047f62cedca76a86ccb7a176369121bbbd07fd9e2e36f2fb6a8a54195048"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1541512800,
    0,
    500};

// Regtest Checkpoints
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x72b85ddf160e1d9f9f14b56b4512e13fcee2cdb0ed9967a8c266d970d6ea0c86"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1541511600,
    0,
    100
};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xe8;
        pchMessageStart[1] = 0xd3;
        pchMessageStart[2] = 0x2b;
        pchMessageStart[3] = 0xec;
        vAlertPubKey = ParseHex("045dc798767160a7a4b0b8f630a31e537032ebf262d3df4adf5ba50360163704074effd884ede9f079bc0b522162b131bec4717143474a648f2fccc05acc890ad7");
        nDefaultPort = 15600;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // 20 CryptradeCoin starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 525600;  // One year
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // CryptradeCoin: 1 minute
        nTargetSpacingSlowLaunch = 2 * 60;  // CryptradeCoin: 2 minutes (Slow launch - Block 60)
        nTargetSpacing = 1 * 60;  // CryptradeCoin: 1 minute
        nMaturity = 49;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 24000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 60;
        nModifierUpdateBlock = 999999999;
        nZerocoinStartHeight = 61;
        nAccumulatorStartHeight = 1;
        nZerocoinStartTime = 1542240000; // Start since blockchain launch
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
            genesis.nTime = 1542240000
            genesis.nNonce = 236551
            genesis.nVersion = 1
            genesis.GetHash = 000003f46e57c04e31374710022a6685abea12cb99960dfe96eaaa430edc670f
            genesis.hashMerkleRoot = 90d274dca16659997d8f5fc9644127d260087d4a39ca61ba9b3334482aa8c55d

         */
        const char* pszTimestamp = "Cryptrade Decentralized Cryptocurrency Trading Platform - Decentralize the Future";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0402355d46092b7003a88b76a285caec1cd1155266d9e1091c91a05a131eb452f121c008bbdc4833f1cf961bf84cba42153cfa7fb8c91ef072039c2818b4639aa9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1542240000; // Thursday, 15-Nov-18 00:00:00 UTC
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 84641;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000007270501d1029bb3661884afd701194f06a134455a28bfc5ef294b7ae862"));
        assert(genesis.hashMerkleRoot == uint256("0x0399978b0171ce7f11f9349bd60ff7c3cd2ec3653e1bff0ea7c625f449655aab"));

        vSeeds.push_back(CDNSSeedData("m1.seed.cryptrade.io", "m1.seed.cryptrade.io")); // mainnet seed1
        vSeeds.push_back(CDNSSeedData("m2.seed.cryptrade.io", "m2.seed.cryptrade.io")); // mainnet seed2
        vSeeds.push_back(CDNSSeedData("m3.seed.cryptrade.io", "m3.seed.cryptrade.io")); // mainnet seed3
        vSeeds.push_back(CDNSSeedData("m4.seed.cryptrade.io", "m4.seed.cryptrade.io")); // mainnet seed4
        vSeeds.push_back(CDNSSeedData("m5.seed.cryptrade.io", "m5.seed.cryptrade.io")); // mainnet seed5
        vSeeds.push_back(CDNSSeedData("m6.seed.cryptrade.io", "m6.seed.cryptrade.io")); // mainnet seed6
        vSeeds.push_back(CDNSSeedData("m7.seed.cryptrade.io", "m7.seed.cryptrade.io")); // mainnet seed7
        vSeeds.push_back(CDNSSeedData("m8.seed.cryptrade.io", "m8.seed.cryptrade.io")); // mainnet seed8
        vSeeds.push_back(CDNSSeedData("m9.seed.cryptrade.io", "m9.seed.cryptrade.io")); // mainnet seed9

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28); // Mainnet cryptradecoin addresses start with 'C'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 65); // Mainnet cryptradecoin script addresses start with 'T'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 209); // Mainnet cryptradecoin private keys start with 'X'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 1135
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x1d)(0xfc).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04f6e088bf5eeb6bdf2e93d2340a91c2768a1883df16eb11fb8372bee043cf8af973ef1d4b74698ac3f92e7eb81adf3c4bdb5c469ba8a693e7b654c6233cea5b43";
        strObfuscationPoolDummyAddress = "CTKfSJYXnm6N5WgkzRLy543Wmc6zSFR7Tk";
        nStartMasternodePayments = 1542240000 + 10800; // Three hour after blockchain launch

        /** Zerocoin */
        zerocoinModulus = "0xc95577b6dce0049b0a20c779af38079355abadde1a1d80c353f6cb697a7ae5a087bad39caa5798478551d0f9d91e6267716506f32412de1d19d17588765eb9502b85c6a18abdb05791cfd8b734e960281193705eeece210920cc922b3af3ceb178bf12c22eb565d5767fbf19545639be8953c2c38ffad41f3371e4aac750ac2d7bd614b3faabb453081d5d88fdbb803657a980bc93707e4b14233a2358c97763bf28f7c933206071477e8b371f229bc9ce7d6ef0ed7163aa5dfe13bc15f7816348b328fa2c1e69d5c88f7b94cee7829d56d1842d77d7bb8692e9fc7b7db059836500de8d57eb43c345feb58671503b932829112941367996b03871300f25efb5";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * ZCENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xe7;
        pchMessageStart[1] = 0x3b;
        pchMessageStart[2] = 0xf6;
        pchMessageStart[3] = 0x5c;
        vAlertPubKey = ParseHex("04f088990cd13f193835405afe9ac3195d6074c2dbbf8c919b32e749a8d6ad767c6d3adc7a5e601364fb034ead609c63054d35d9d21f3673a1383a312525d7c9e1");
        nDefaultPort = 16600;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // CryptradeCoin: 1 minute
        nTargetSpacing = 1 * 60;  // CryptradeCoin: 1 minute
        nLastPOWBlock = 60;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 24000000 * COIN;
        nZerocoinStartHeight = 61;
        nZerocoinStartTime = 1541512800;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1541512800; // Tuesday, November 6, 2018 2:00:00 PM GMT
        genesis.nNonce = 628905;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000047f62cedca76a86ccb7a176369121bbbd07fd9e2e36f2fb6a8a54195048"));
        assert(genesis.hashMerkleRoot == uint256("0x0399978b0171ce7f11f9349bd60ff7c3cd2ec3653e1bff0ea7c625f449655aab"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("t1.seed.cryptrade.io", "t1.seed.cryptrade.io")); // testnet seed1
        vSeeds.push_back(CDNSSeedData("t2.seed.cryptrade.io", "t2.seed.cryptrade.io")); // testnet seed2

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 87); // Testnet cryptradecoin addresses start with 'c'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet cryptradecoin script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet cryptradecoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptradecoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptradecoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "048555b6f3d3210d9993c818743e52b4e697aa2bd71f790f2f471846b79b7d98182f06e5c6aee2cd34c9f8ba7ca08c17c437071e669fb2eb25933519563348b395";
        strObfuscationPoolDummyAddress = "c9mMVNweU5RDEYCdBcgEYUw4BaxpiFovmL";
        nStartMasternodePayments = 1541512800 + 10800; // Three hour after blockchain launch
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x8c;
        pchMessageStart[1] = 0xe4;
        pchMessageStart[2] = 0xef;
        pchMessageStart[3] = 0x5f;
        nDefaultPort = 17600;
        nSubsidyHalvingInterval = 262800; // Half a year
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // CryptradeCoin: 1 day
        nTargetSpacing = 1 * 60;        // CryptradeCoin: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1541511600;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 5;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x72b85ddf160e1d9f9f14b56b4512e13fcee2cdb0ed9967a8c266d970d6ea0c86"));
        assert(genesis.hashMerkleRoot == uint256("0x0399978b0171ce7f11f9349bd60ff7c3cd2ec3653e1bff0ea7c625f449655aab"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18600;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
