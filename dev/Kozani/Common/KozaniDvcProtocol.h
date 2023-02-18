#pragma once

namespace Microsoft::Kozani::DvcProtocol
{
    const char DvcChannelName[] = "KozaniDvc";

    const size_t MaxProtocolDataUnitSize = 64 * 1024;

    enum ProtocolDataUnitType
    {
        ConnectionAck = 0,
        AppActivationCommand = 1,
        AppActivationResult = 2,
        AppTerminationCommand = 3,
        AppTerminationResult = 4
    };

    struct ProtocolDataUnit_Raw
    {
        // Size of the entire PDU
        UINT32 size;
        ProtocolDataUnitType type;
        
        // Place holder of the starting point of payload data. Accessed using &data.
        BYTE data;
    };

    struct PDU_ConnectionAck_Raw
    {
        UINT32 connectionIdLength;
        char connectionId;
    };

    struct ProtocolDataUnit
    {
        ProtocolDataUnitType type;
        UINT32 dataSize;
        BYTE* data;
    };

    struct PDU_ConnectionAck
    {
        std::string connectionId;
    };

    std::vector<BYTE> CreateConnectionAckPDU(PCSTR connectionId)
    {
        size_t connectionIdLength = strlen(connectionId);
        if (connectionIdLength > MaxProtocolDataUnitSize - sizeof(ProtocolDataUnit_Raw) - sizeof(PDU_ConnectionAck_Raw))
        {
            THROW_WIN32_MSG(ERROR_LABEL_TOO_LONG, "Connection ID too long");
        }

        UINT32 size = static_cast<UINT32>(sizeof(ProtocolDataUnit_Raw) + sizeof(PDU_ConnectionAck_Raw) + connectionIdLength);

        std::vector<BYTE> buffer;
        buffer.resize(size);

        ProtocolDataUnit_Raw* pdu = reinterpret_cast<ProtocolDataUnit_Raw*>(buffer.data());
        pdu->size = size;
        pdu->type = ProtocolDataUnitType::ConnectionAck;

        PDU_ConnectionAck_Raw* pduAck = reinterpret_cast<PDU_ConnectionAck_Raw*>(&(pdu->data));
        pduAck->connectionIdLength = static_cast<UINT32>(connectionIdLength);
        memcpy(&pduAck->connectionId, connectionId, connectionIdLength);

        return std::move(buffer);
    }

    void DecodePDURaw(BYTE* buffer, UINT32 size, _Out_ ProtocolDataUnit& pdu)
    {
        ProtocolDataUnit_Raw* pduRaw = reinterpret_cast<ProtocolDataUnit_Raw*>(buffer);
        if (pduRaw->size > size)
        {
            THROW_WIN32(ERROR_INVALID_DATA);
        }

        pdu.type = pduRaw->type;
        pdu.dataSize = pduRaw->size - sizeof(ProtocolDataUnit_Raw);
        pdu.data = &pduRaw->data;
    }

    void DecodeConnectionAckPDURaw(BYTE* buffer, UINT32 size, _Out_ PDU_ConnectionAck& pduAck)
    {
        PDU_ConnectionAck_Raw* pduAckRaw = reinterpret_cast<PDU_ConnectionAck_Raw*>(buffer);
        pduAck.connectionId.assign(&pduAckRaw->connectionId, pduAckRaw->connectionIdLength);
    }
}