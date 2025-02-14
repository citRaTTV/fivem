﻿#pragma once

#include "SerializableComponent.h"
#include "SerializableProperty.h"
#include "SerializableStorageType.h"

namespace net::packet
{
class ClientIQuit : public SerializableComponent
{
public:
	// todo: uses null terminator, in future net version remove it
	SerializableProperty<Span<const char>, storage_type::ConstrainedStreamTail<2, 1024>> reason;

	template<typename T>
	bool Process(T& stream)
	{
		return ProcessPropertiesInOrder<T>(
			stream,
			reason
		);
	}
};

/// <summary>
/// Request from the client to the server for dropping the connection.
/// </summary>
class ClientIQuitPacket : public SerializableComponent
{
public:
	SerializableProperty<uint32_t> type{ net::force_consteval<uint32_t, HashRageString("msgIQuit")> };
	ClientIQuit data;

	template<typename T>
	bool Process(T& stream)
	{
		return ProcessPropertiesInOrder<T>(
			stream,
			type,
			data
		);
	}
};
}
