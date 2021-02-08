#pragma once

#include "Event.h"

class JoystickConnectEvent : public Event
{
public:
	JoystickConnectEvent(int jid, bool connect);

	inline bool getJID() const { return jid; }
	inline bool hasConnected() const { return connect; }

	virtual std::string toString() const override;
private:
	int jid;
	bool connect;
};

class MonitorConnectEvent : public Event
{
public:
	MonitorConnectEvent(bool connect);

	inline bool hasConnected() const { return connect; }

	virtual std::string toString() const override;
private:
	bool connect;
};
