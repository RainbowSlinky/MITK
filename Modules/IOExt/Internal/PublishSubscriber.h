#ifndef PublishSubscriber_h_included
#define PublishSubscriber_h_included

#include "IPublishSubscriberService.h"

#include <usModuleContext.h>
#include <usServiceInterface.h>

#include <functional>
#include <memory>

namespace mitk
{
	class IOExtActivator;

	class PublishSubscriber
	{
		private:
			

		public:
			virtual ~PublishSubscriber();
			void Register(const std::function<void(void)> method);
			void Fire();
			static PublishSubscriber* GetInstance();
			friend class mitk::IOExtActivator;

		protected:
			PublishSubscriber() {};
			PublishSubscriber(const PublishSubscriber&);
			PublishSubscriber& operator=(const PublishSubscriber&);
			
			static PublishSubscriber* m_PublisherSubscriber;
			std::function<void(void)> m_callBackMethod;
	};

}
US_DECLARE_SERVICE_INTERFACE(mitk::PublishSubscriber, "my_service")
#endif