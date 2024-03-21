#ifndef MESSAGE_GRAPH_NODE_HIDE_H
#define MESSAGE_GRAPH_NODE_HIDE_H

#include "Message.h"
#include "TabId.h"
#include "types.h"

class MessageGraphNodeHide: public Message<MessageGraphNodeHide>
{
public:
	MessageGraphNodeHide(Id tokenId): tokenId(tokenId)
	{
		setSchedulerId(TabId::currentTab());
	}

	static const std::string getStaticType()
	{
		return "MessageGraphNodeHide";
	}

	void print(std::wostream& os) const override
	{
		os << tokenId;
	}

	const Id tokenId;
};

#endif	  // MESSAGE_GRAPH_NODE_HIDE_H
