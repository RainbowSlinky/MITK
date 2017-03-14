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

#include "QmitkExtAppWorkbenchAdvisor.h"
#include "internal/QmitkExtApplicationPlugin.h"

#include <QmitkExtWorkbenchWindowAdvisor.h>

const QString QmitkExtAppWorkbenchAdvisor::DEFAULT_PERSPECTIVE_ID =
    "org.mitk.extapp.defaultperspective";

void
QmitkExtAppWorkbenchAdvisor::Initialize(berry::IWorkbenchConfigurer::Pointer configurer)
{
  berry::QtWorkbenchAdvisor::Initialize(configurer);

  configurer->SetSaveAndRestore(true);
  //configurer->RestoreWorkbenchWindow()
}

berry::WorkbenchWindowAdvisor*
QmitkExtAppWorkbenchAdvisor::CreateWorkbenchWindowAdvisor(
        berry::IWorkbenchWindowConfigurer::Pointer configurer)
{
  QmitkExtWorkbenchWindowAdvisor* advisor = new
    QmitkExtWorkbenchWindowAdvisor(this, configurer);

  // Exclude the help perspective from org.blueberry.ui.qt.help from
  // the normal perspective list.
  // The perspective gets a dedicated menu entry in the help menu
  QList<QString> excludePerspectives;
  excludePerspectives.push_back("org.blueberry.perspectives.help");
  advisor->SetPerspectiveExcludeList(excludePerspectives);

  // Exclude some views from the normal view list
  QList<QString> excludeViews;
  excludeViews.push_back("org.mitk.views.modules");
  excludeViews.push_back("org.blueberry.ui.internal.introview");
  excludeViews.push_back("org.blueberry.views.helpcontents");
  excludeViews.push_back("org.blueberry.views.helpindex");
  excludeViews.push_back("org.blueberry.views.helpsearch");
  excludeViews.push_back("org.mitk.views.properties");
  excludeViews.push_back("org.mitk.views.xnat.treebrowser");
  excludeViews.push_back("org.mitk.views.deformableclippingplane");
  excludeViews.push_back("org.mitk.views.segmentationutilities");
	
  advisor->SetViewExcludeList(excludeViews);

  advisor->SetWindowIcon(":/org.mitk.gui.qt.extapplication/icon.png");
  
  //Leo
  advisor->ShowViewToolbar(true);
  advisor->ShowPerspectiveToolbar(false);
  advisor->ShowVersionInfo(false);
  advisor->ShowMitkVersionInfo(false);

  return advisor;
  //return new QmitkExtWorkbenchWindowAdvisor(this, configurer);
}

QString QmitkExtAppWorkbenchAdvisor::GetInitialWindowPerspectiveId()
{
  return DEFAULT_PERSPECTIVE_ID;
}
