#include "PublishSubscriber.h"

//micro service includes
#include <usServiceReference.h>
#include <usGetModuleContext.h>

mitk::PublishSubscriber* mitk::PublishSubscriber::m_PublisherSubscriber = NULL;


mitk::PublishSubscriber::~PublishSubscriber()
{
	mitk::PublishSubscriber::m_PublisherSubscriber = NULL;
}

void mitk::PublishSubscriber::Register(const std::function<void(void)> method)
{
	this->m_callBackMethod = method;
}

void mitk::PublishSubscriber::Fire()
{
	this->m_callBackMethod();
}

mitk::PublishSubscriber* mitk::PublishSubscriber::GetInstance()
{
	static us::ServiceReference<mitk::PublishSubscriber> serviceRef;
	static us::ModuleContext* context = us::GetModuleContext();
	if (!serviceRef)
	{
		// This is either the first time GetInstance() was called,
		// or a SingletonOneService instance has not yet been registered.
		serviceRef = context->GetServiceReference<mitk::PublishSubscriber>();
	}
	if (serviceRef)
	{
		// We have a valid service reference. It always points to the service
		// with the lowest id (usually the one which was registered first).
		// This still might return a null pointer, if all SingletonOneService
		// instances have been unregistered (during unloading of the library,
		// for example).
		return context->GetService(serviceRef);
	}
	else
	{
		// No SingletonOneService instance was registered yet.
		return 0;
	}

	//if (!mitk::PublishSubscriber::m_PublisherSubscriber)
	//	mitk::PublishSubscriber::m_PublisherSubscriber = new mitk::PublishSubscriber;

	//return mitk::PublishSubscriber::m_PublisherSubscriber;
}