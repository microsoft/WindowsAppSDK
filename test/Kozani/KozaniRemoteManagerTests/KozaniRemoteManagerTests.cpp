// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "KozaniDvcProtocol.h"

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

using namespace Microsoft::Kozani::DvcProtocol;

namespace Test::KozaniRemoteManagerTests
{
    class KozaniRemoteManagerTests
    {
    public:
        BEGIN_TEST_CLASS(KozaniRemoteManagerTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            //::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            //::TB::Cleanup();
            return true;
        }

        // TODO Replace this with your own tests
        TEST_METHOD(DvcPDU_CreationAndDecode)
        {
            PCSTR connectionId{ "abcdefg-khkhk-123456" };
            std::vector<BYTE> ackPDURaw{ CreateConnectionAckPDU(connectionId) };

            ProtocolDataUnit pdu{};
            PDU_ConnectionAck pduAck{};
            DecodePDURaw(ackPDURaw.data(), ackPDURaw.size(), pdu);

            VERIFY_ARE_EQUAL(pdu.type, ProtocolDataUnitType::ConnectionAck);
            DecodeConnectionAckPDURaw(pdu.data, pdu.dataSize, pduAck);
            VERIFY_ARE_EQUAL(pduAck.connectionId, connectionId);
        }
    };
}
