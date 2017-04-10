/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "mitkIOExtActivator.h"

#include "mitkSceneFileReader.h"
#include "mitkObjFileReaderService.h"
#include "mitkVtkUnstructuredGridReader.h"
#include "mitkPlyFileWriterService.h"
#include "mitkPlyFileReaderService.h"

#include <usServiceProperties.h>
#include <usGetModuleContext.h>
#include <usModuleActivator.h>
#include <usModuleContext.h>
#include <usModule.h>

namespace mitk {

void IOExtActivator::Load(us::ModuleContext* context)
{
  m_SceneReader.reset(new SceneFileReader());

  m_VtkUnstructuredGridReader.reset(new VtkUnstructuredGridReader());
  m_ObjReader.reset(new ObjFileReaderService());

  m_PlyReader.reset(new PlyFileReaderService());
  m_ObjWriter.reset(new PlyFileWriterService());

  m_PubSub.reset(new mitk::PublishSubscriber);
  context->RegisterService<mitk::PublishSubscriber>(m_PubSub.get());
  
  context->AddServiceListener(this, &IOExtActivator::SceneLoaded);

}

void IOExtActivator::Unload(us::ModuleContext* context)
{
	context->RemoveServiceListener(this, &IOExtActivator::SceneLoaded);
}

void IOExtActivator::SceneLoaded(const us::ServiceEvent m_event)
{
	std::string objectClass = us::ref_any_cast<std::vector<std::string> >(m_event.GetServiceReference().GetProperty(us::ServiceConstants::OBJECTCLASS())).front();
	if (m_event.GetType() == us::ServiceEvent::REGISTERED)
	{
		std::cout << "Ex1: Service of type " << objectClass << " registered." << std::endl;
	}
	else if (m_event.GetType() == us::ServiceEvent::UNREGISTERING)
	{
		std::cout << "Ex1: Service of type " << objectClass << " unregistered." << std::endl;
	}
	else if (m_event.GetType() == us::ServiceEvent::MODIFIED)
	{
		std::cout << "Ex1: Service of type " << objectClass << " modified." << std::endl;
	}
}

}



US_EXPORT_MODULE_ACTIVATOR(mitk::IOExtActivator)
