#ifndef STATUS_CONTROLLER_H
#define STATUS_CONTROLLER_H

#include "Controller.h"

#include "MessageClearStatusView.h"
#include "MessageListener.h"
#include "MessageShowStatus.h"
#include "MessageStatus.h"
#include "MessageStatusFilterChanged.h"
#include "Status.h"

class StatusView;
class StorageAccess;

class StatusController
	: public Controller
	, public MessageListener<MessageClearStatusView>
	, public MessageListener<MessageShowStatus>
	, public MessageListener<MessageStatus>
	, public MessageListener<MessageStatusFilterChanged>
{
public:
	StatusController();
	~StatusController() override;

private:
	StatusView* getView() const;

	void clear() override;

	void handleMessage(MessageClearStatusView* message) override;
	void handleMessage(MessageShowStatus* message) override;
	void handleMessage(MessageStatus* message) override;
	void handleMessage(MessageStatusFilterChanged* message) override;

	void addStatus(const std::vector<Status> status);

	std::vector<Status> m_status;
	StatusFilter m_statusFilter;
};

#endif	  // STATUS_CONTROLLER_H
