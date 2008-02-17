/***************************************************************************
 *   Copyright (C) 2007 by Christoph Thelen                                *
 *   doc_bacardi@users.sourceforge.net                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "muhkuh_id.h"
#include "muhkuh_configDialog.h"
#include "muhkuh_config_reposEntryDialog.h"

#include "icons/famfamfam_silk_icons_v013/accept.xpm"
#include "icons/famfamfam_silk_icons_v013/bullet_green.xpm"
#include "icons/famfamfam_silk_icons_v013/bullet_yellow.xpm"
#include "icons/famfamfam_silk_icons_v013/cancel.xpm"
#include "icons/famfamfam_silk_icons_v013/database.xpm"
#include "icons/famfamfam_silk_icons_v013/database_add.xpm"
#include "icons/famfamfam_silk_icons_v013/database_delete.xpm"
#include "icons/famfamfam_silk_icons_v013/database_edit.xpm"
#include "icons/famfamfam_silk_icons_v013/exclamation.xpm"
#include "icons/famfamfam_silk_icons_v013/key.xpm"
#include "icons/famfamfam_silk_icons_v013/plugin.xpm"
#include "icons/famfamfam_silk_icons_v013/plugin_add.xpm"
#include "icons/famfamfam_silk_icons_v013/plugin_delete.xpm"
#include "icons/famfamfam_silk_icons_v013/plugin_disabled.xpm"
#include "icons/famfamfam_silk_icons_v013/plugin_go.xpm"
#include "icons/famfamfam_silk_icons_v013/tag_blue.xpm"


BEGIN_EVENT_TABLE(muhkuh_configDialog, wxDialog)
	EVT_TOOL(muhkuh_configDialog_AddRepository,			muhkuh_configDialog::OnNewRepositoryButton)
	EVT_TOOL(muhkuh_configDialog_EditRepository,			muhkuh_configDialog::OnEditRepositoryButton)
	EVT_TOOL(muhkuh_configDialog_RemoveRepository,			muhkuh_configDialog::OnDeleteRepositoryButton)
	EVT_TREE_SEL_CHANGED(muhkuh_configDialog_RepositoryList,	muhkuh_configDialog::OnRepositorySelect)

	EVT_TOOL(muhkuh_configDialog_AddPlugin,				muhkuh_configDialog::OnAddPluginButton)
	EVT_TOOL(muhkuh_configDialog_RemovePlugin,			muhkuh_configDialog::OnRemovePluginButton)
	EVT_TOOL(muhkuh_configDialog_EnablePlugin,			muhkuh_configDialog::OnEnablePluginButton)
	EVT_TOOL(muhkuh_configDialog_DisablePlugin,			muhkuh_configDialog::OnDisablePluginButton)
	EVT_TREE_SEL_CHANGED(muhkuh_configDialog_PluginList,		muhkuh_configDialog::OnPluginSelectionChanged)
	EVT_TREE_SEL_CHANGING(muhkuh_configDialog_PluginList,		muhkuh_configDialog::OnPluginSelectionChanging)
END_EVENT_TABLE()


muhkuh_configDialog::muhkuh_configDialog(wxWindow *parent, const wxString strApplicationPath, muhkuh_plugin_manager *ptPluginManager, muhkuh_repository_manager *ptRepositoryManager)
 : wxDialog(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER)
 , m_ptRepositoryManager(ptRepositoryManager)
 , m_ptPluginManager(ptPluginManager)
{
	size_t sizCnt, sizIdx;


	m_strApplicationPath = strApplicationPath;

	// set the title
	SetTitle(_("Muhkuh Settings"));

	// create the controls
	createControls();

	// loop over all repositories and add them to the list
	sizIdx = 0;
	sizCnt = m_ptRepositoryManager->GetRepositoryCount();
	while(sizIdx<sizCnt)
	{
		ShowNewRepository(sizIdx);
		// next entry
		++sizIdx;
	}

	// loop over all plugins and add them to the list
	sizIdx = 0;
	sizCnt = m_ptPluginManager->getPluginCount();
	while(sizIdx<sizCnt)
	{
		ShowNewPlugin(sizIdx);
		++sizIdx;
	}
}


void muhkuh_configDialog::createControls(void)
{
	wxBoxSizer *ptMainSizer;
	wxBoxSizer *ptbuttonSizer;
	wxImageList *ptTreeBookImageList;
	wxButton *ptButtonOk;
	wxButton *ptButtonCancel;


	// init the controls
	ptMainSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(ptMainSizer);

	// create the treebook
	m_treeBook = new wxTreebook(this, muhkuh_configDialog_TreeBook);
	ptMainSizer->Add(m_treeBook, 1, wxEXPAND);
	ptTreeBookImageList = new wxImageList(16, 16, true, 2);
	ptTreeBookImageList->Add( wxIcon(icon_famfamfam_silk_database) );
	ptTreeBookImageList->Add( wxIcon(icon_famfamfam_silk_plugin) );
	m_treeBook->AssignImageList(ptTreeBookImageList);

	m_treeBook->AddPage(createControls_repository(m_treeBook), _("Repositories"), true, 0);
	m_treeBook->AddPage(createControls_plugin(m_treeBook), _("Plugins"), false, 1);

	ptbuttonSizer = new wxBoxSizer(wxHORIZONTAL);
	ptMainSizer->Add(ptbuttonSizer, 0, wxEXPAND);
	ptButtonOk = new wxButton(this, wxID_OK);
	ptButtonCancel = new wxButton(this, wxID_CANCEL);
	ptbuttonSizer->AddStretchSpacer(1);
	ptbuttonSizer->Add(ptButtonOk);
	ptbuttonSizer->AddStretchSpacer(1);
	ptbuttonSizer->Add(ptButtonCancel);
	ptbuttonSizer->AddStretchSpacer(1);

	ptMainSizer->SetSizeHints(this);
}


wxPanel *muhkuh_configDialog::createControls_repository(wxWindow *ptParent)
{
	wxPanel *ptRepositoryPanel;
	wxBoxSizer *ptMainSizer;
	wxBoxSizer *ptbuttonSizer;
	wxImageList *ptRepoImageList;


	// create the imagelist
	ptRepoImageList = muhkuh_repository::CreateNewImageList();

	// create the repository page
	ptRepositoryPanel = new wxPanel(ptParent);

	// create the main sizer
	ptMainSizer = new wxBoxSizer(wxVERTICAL);
	ptRepositoryPanel->SetSizer(ptMainSizer);

	// create the repository list
	m_repositoryTree = new wxTreeCtrl(ptRepositoryPanel, muhkuh_configDialog_RepositoryList, wxDefaultPosition, wxDefaultSize, wxTR_NO_BUTTONS|wxTR_NO_LINES|wxTR_HIDE_ROOT|wxTR_SINGLE);
	m_repositoryTree->AddRoot(wxEmptyString);
	m_repositoryTree->AssignImageList(ptRepoImageList);
	ptMainSizer->Add(m_repositoryTree, 1, wxEXPAND);

	// create the repository toolbar
	m_repositoryToolBar = new wxToolBar(ptRepositoryPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,  wxTB_HORIZONTAL|wxNO_BORDER|wxTB_TEXT);
	m_repositoryToolBar->AddTool(muhkuh_configDialog_AddRepository, _("Add"), icon_famfamfam_silk_database_add, wxNullBitmap, wxITEM_NORMAL, _("Add Repository"), _("Add a new repository to the list"));
	m_repositoryToolBar->AddTool(muhkuh_configDialog_EditRepository, _("Edit"), icon_famfamfam_silk_database_edit, wxNullBitmap, wxITEM_NORMAL, _("Edit Repository"), _("Edit the settings of the selected repository"));
	m_repositoryToolBar->EnableTool(muhkuh_configDialog_EditRepository, false);
	m_repositoryToolBar->AddTool(muhkuh_configDialog_RemoveRepository, _("Remove"), icon_famfamfam_silk_database_delete, wxNullBitmap, wxITEM_NORMAL, _("Remove Repository"), _("Remove the selected repository from the list"));
	m_repositoryToolBar->EnableTool(muhkuh_configDialog_RemoveRepository, false);
	m_repositoryToolBar->Realize();
	ptMainSizer->Add(m_repositoryToolBar, 0, wxEXPAND);

	return ptRepositoryPanel;
}


wxPanel *muhkuh_configDialog::createControls_plugin(wxWindow *ptParent)
{
	wxPanel *ptPluginPanel;
	wxBoxSizer *ptMainSizer;
	wxImageList *ptPluginImageList;


	// create imagelist for 5 images with 16x16 pixels
	ptPluginImageList = new wxImageList(16, 16, true, 5);
	ptPluginImageList->Add( wxIcon(icon_famfamfam_silk_bullet_yellow) );
	ptPluginImageList->Add( wxIcon(icon_famfamfam_silk_bullet_green) );
	ptPluginImageList->Add( wxIcon(icon_famfamfam_silk_exclamation) );
	ptPluginImageList->Add( wxIcon(icon_famfamfam_silk_key) );
	ptPluginImageList->Add( wxIcon(icon_famfamfam_silk_tag_blue) );

	// create the plugin page
	ptPluginPanel = new wxPanel(ptParent);

	// create the main sizer
	ptMainSizer = new wxBoxSizer(wxVERTICAL);
	ptPluginPanel->SetSizer(ptMainSizer);

	// create the plugin list
	m_pluginTree = new wxTreeCtrl(ptPluginPanel, muhkuh_configDialog_PluginList, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_NO_LINES|wxTR_HIDE_ROOT|wxTR_SINGLE);
	m_pluginTree->AddRoot(wxEmptyString);
	m_pluginTree->AssignImageList(ptPluginImageList);
	ptMainSizer->Add(m_pluginTree, 1, wxEXPAND);

	// create the plugin toolbar
	m_pluginToolBar = new wxToolBar(ptPluginPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,  wxTB_HORIZONTAL|wxNO_BORDER|wxTB_TEXT);
	m_pluginToolBar->AddTool(muhkuh_configDialog_AddPlugin, _("Add"), icon_famfamfam_silk_plugin_add, wxNullBitmap, wxITEM_NORMAL, _("Add Plugin"), _("Add a new plugin to the list"));
	m_pluginToolBar->AddTool(muhkuh_configDialog_RemovePlugin, _("Remove"), icon_famfamfam_silk_plugin_delete, wxNullBitmap, wxITEM_NORMAL, _("Remove Plugin"), _("Remove the selected plugin from the list"));
	m_pluginToolBar->EnableTool(muhkuh_configDialog_RemovePlugin, false);
	m_pluginToolBar->AddTool(muhkuh_configDialog_EnablePlugin, _("Enable"), icon_famfamfam_silk_plugin_go, wxNullBitmap, wxITEM_NORMAL, _("Enable Plugin"), _("Enable the selected plugin"));
	m_pluginToolBar->EnableTool(muhkuh_configDialog_EnablePlugin, false);
	m_pluginToolBar->AddTool(muhkuh_configDialog_DisablePlugin, _("Disable"), icon_famfamfam_silk_plugin_disabled, wxNullBitmap, wxITEM_NORMAL, _("Disable Plugin"), _("Disable the selected plugin"));
	m_pluginToolBar->EnableTool(muhkuh_configDialog_DisablePlugin, false);
	m_pluginToolBar->Realize();
	ptMainSizer->Add(m_pluginToolBar, 0, wxEXPAND);

	return ptPluginPanel;
}


void muhkuh_configDialog::OnNewRepositoryButton(wxCommandEvent &WXUNUSED(event))
{
	muhkuh_config_reposEntryDialog *ptEntryDialog;
	muhkuh_repository *ptRepos;
	long lIdx;


	ptRepos = new muhkuh_repository(_("new repository"));
	ptEntryDialog = new muhkuh_config_reposEntryDialog(this, m_strApplicationPath, ptRepos);
	if( ptEntryDialog->ShowModal()==wxID_OK )
	{
		// add to list
		lIdx = m_ptRepositoryManager->addRepository(ptRepos);
		// show
		ShowNewRepository(lIdx);
	}
	else
	{
		delete ptRepos;
	}
	ptEntryDialog->Destroy();
}


void muhkuh_configDialog::OnEditRepositoryButton(wxCommandEvent &WXUNUSED(event))
{
	wxTreeItemId tItem;
	repositoryTreeItemData *ptData;
	long lRepositoryIdx;
	muhkuh_config_reposEntryDialog *ptEntryDialog;
	muhkuh_repository *ptRepos;


	// get the selected item
	tItem = m_repositoryTree->GetSelection();
	// was something selected?
	if( tItem.IsOk()==true )
	{
		// get the repository id
		ptData = (repositoryTreeItemData*)m_pluginTree->GetItemData(tItem);
		if( ptData!=NULL )
		{
			lRepositoryIdx = ptData->GetRepositoryId();

			ptRepos = m_ptRepositoryManager->GetRepository(lRepositoryIdx);

			// clone the entry
			ptEntryDialog = new muhkuh_config_reposEntryDialog(this, m_strApplicationPath, ptRepos);
			if( ptEntryDialog->ShowModal()==wxID_OK )
			{
				// update the item
				m_repositoryTree->SetItemText(tItem, ptRepos->GetStringRepresentation());
				m_repositoryTree->SetItemImage(tItem, ptRepos->GetImageListIndex());
			}
			ptEntryDialog->Destroy();
		}
	}
}


void muhkuh_configDialog::OnDeleteRepositoryButton(wxCommandEvent &WXUNUSED(event))
{
	wxTreeItemId tItem;
	repositoryTreeItemData *ptData;
	long lRepositoryIdx;
	muhkuh_config_reposEntryDialog *ptEntryDialog;
	muhkuh_repository *ptRepos;


	// get the selected item
	tItem = m_repositoryTree->GetSelection();
	// was something selected?
	if( tItem.IsOk()==true )
	{
		// get the repository id
		ptData = (repositoryTreeItemData*)m_pluginTree->GetItemData(tItem);
		if( ptData!=NULL )
		{
			lRepositoryIdx = ptData->GetRepositoryId();

			// erase from the listctrl
			m_repositoryTree->Delete(tItem);
			// erase from the vector
			m_ptRepositoryManager->removeRepository(lRepositoryIdx);
		}
	}
}


void muhkuh_configDialog::OnRepositorySelect(wxTreeEvent &event)
{
	wxTreeItemId tItem;
	long lIdx;
	bool fPluginSelected;
	repositoryTreeItemData *ptData;


	tItem = event.GetItem();
	fPluginSelected = tItem.IsOk();
	if( fPluginSelected==true )
	{
		ptData = (repositoryTreeItemData*)m_pluginTree->GetItemData(tItem);
		fPluginSelected = (ptData!=NULL);
	}	
	m_repositoryToolBar->EnableTool(muhkuh_configDialog_EditRepository,	fPluginSelected);
	m_repositoryToolBar->EnableTool(muhkuh_configDialog_RemoveRepository,	fPluginSelected);
}


void muhkuh_configDialog::OnAddPluginButton(wxCommandEvent &WXUNUSED(event))
{
	wxFileDialog *pluginDialog;
	wxFileName fileName;
	wxString strPluginName;
	wxString strDialogInitPath;
	long lIdx;
	bool fPluginIsOk;


	strDialogInitPath = wxEmptyString;
/*
	if( m_fUseRelativePaths==true )
	{
		fileName.Assign(strDialogInitPath);
		if(fileName.Normalize(wxPATH_NORM_ALL, m_strApplicationPath ,wxPATH_NATIVE))
		{
			strDialogInitPath = fileName.GetFullPath();
		}
	}
*/
	pluginDialog = new wxFileDialog(this, _("Select the new plugin"), strDialogInitPath, wxEmptyString, wxT("*.xml"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

	if( pluginDialog->ShowModal()==wxID_OK )
	{
		strPluginName = pluginDialog->GetPath();
		wxLogMessage(_("open plugin '%s'"), strPluginName.fn_str());
		lIdx = m_ptPluginManager->addPlugin(strPluginName);
		if( lIdx>=0 )
		{
			// do not accept broken plugins
			fPluginIsOk = m_ptPluginManager->IsOk(lIdx);
			if( fPluginIsOk==true )
			{
				ShowNewPlugin(lIdx);
			}
			else
			{
				m_ptPluginManager->removePlugin(lIdx);
			}
		}
	}
	pluginDialog->Destroy();
}


void muhkuh_configDialog::OnRemovePluginButton(wxCommandEvent &WXUNUSED(event))
{
	wxTreeItemId tItem;
	pluginTreeItemData *ptData;
	long lPluginIdx;


	// get the selected item
	tItem = m_pluginTree->GetSelection();
	// was something selected?
	if( tItem.IsOk()==true )
	{
		// disable all buttons (in case if no update event follows the delete)
		SetPluginButtons(wxTreeItemId());

		// get the plugin id
		ptData = (pluginTreeItemData*)m_pluginTree->GetItemData(tItem);
		if( ptData!=NULL )
		{
			lPluginIdx = ptData->GetPluginId();

			// erase from the tree
			m_pluginTree->Delete(tItem);

			// erase from the manager
			m_ptPluginManager->removePlugin(lPluginIdx);
		}
	}
}


void muhkuh_configDialog::OnEnablePluginButton(wxCommandEvent &WXUNUSED(event))
{
	wxTreeItemId tItem;
	pluginTreeItemData *ptData;
	long lPluginIdx;


	// get the selected item
	tItem = m_pluginTree->GetSelection();
	// was something selected?
	if( tItem.IsOk()==true )
	{
		// get the plugin id
		ptData = (pluginTreeItemData*)m_pluginTree->GetItemData(tItem);
		if( ptData!=NULL )
		{
			lPluginIdx = ptData->GetPluginId();

			m_ptPluginManager->SetEnable(lPluginIdx, true);
			ShowPluginImage(tItem);
			SetPluginButtons(tItem);
		}
	}
}


void muhkuh_configDialog::OnDisablePluginButton(wxCommandEvent &WXUNUSED(event))
{
	wxTreeItemId tItem;
	pluginTreeItemData *ptData;
	long lPluginIdx;


	// get the selected item
	tItem = m_pluginTree->GetSelection();
	// was something selected?
	if( tItem.IsOk()==true )
	{
		// get the plugin id
		ptData = (pluginTreeItemData*)m_pluginTree->GetItemData(tItem);
		if( ptData!=NULL )
		{
			lPluginIdx = ptData->GetPluginId();

			m_ptPluginManager->SetEnable(lPluginIdx, false);
			ShowPluginImage(tItem);
			SetPluginButtons(tItem);
		}
	}
}


void muhkuh_configDialog::OnPluginSelectionChanging(wxTreeEvent &event)
{
	wxTreeItemId tItem;
	pluginTreeItemData *ptData;
	bool fAllowChange;


	// don't allow change by default
	fAllowChange = false;

	// only allow items with tree data to be selected
	tItem = event.GetItem();
	if( tItem.IsOk()==true )
	{
		ptData = (pluginTreeItemData*)m_pluginTree->GetItemData(tItem);
		if( ptData!=NULL )
		{
			fAllowChange = true;
		}
	}

	// allow or veto the change request
	if( fAllowChange==true )
	{
		event.Allow();
	}
	else
	{
		event.Veto();
	}
}


void muhkuh_configDialog::OnPluginSelectionChanged(wxTreeEvent &event)
{
	SetPluginButtons(event.GetItem());
}


void muhkuh_configDialog::SetPluginButtons(wxTreeItemId tItem)
{
	pluginTreeItemData *ptData;
	long lPluginIdx;
	bool fPluginSelected;
	bool fPluginIsOk;
	bool fPluginIsEnabled;
	bool fPluginCanBeEnabled;
	bool fPluginCanBeDisabled;


	fPluginSelected = tItem.IsOk();
	// set default values
	fPluginCanBeEnabled = false;
	fPluginCanBeDisabled = false;

	if( fPluginSelected==true )
	{
		ptData = (pluginTreeItemData*)m_pluginTree->GetItemData(tItem);
		if( ptData!=NULL )
		{
			lPluginIdx = ptData->GetPluginId();
			fPluginIsOk = m_ptPluginManager->IsOk(lPluginIdx);
			fPluginIsEnabled = m_ptPluginManager->GetEnable(lPluginIdx);

			fPluginCanBeEnabled = fPluginSelected && fPluginIsOk && !fPluginIsEnabled;
			fPluginCanBeDisabled = fPluginSelected && fPluginIsOk && fPluginIsEnabled;
		}
	}

	m_pluginToolBar->EnableTool(muhkuh_configDialog_RemovePlugin,	fPluginSelected);
	m_pluginToolBar->EnableTool(muhkuh_configDialog_EnablePlugin,	fPluginCanBeEnabled);
	m_pluginToolBar->EnableTool(muhkuh_configDialog_DisablePlugin,	fPluginCanBeDisabled);
}


void muhkuh_configDialog::ShowNewRepository(long lIdx)
{
	wxTreeItemId tRootItem;
	repositoryTreeItemData *ptData;
	int iImageIdx;
	wxString strName;


	// append all plugins to the root item
	tRootItem = m_repositoryTree->GetRootItem();

	strName = m_ptRepositoryManager->GetStringRepresentation(lIdx);
	iImageIdx = m_ptRepositoryManager->GetImageListIndex(lIdx);
	ptData = new repositoryTreeItemData(lIdx);

	m_repositoryTree->AppendItem(tRootItem, strName, iImageIdx, -1, ptData);
}


void muhkuh_configDialog::ShowNewPlugin(long lIdx)
{
	bool fPluginIsOk;
	wxTreeItemId tRootItem;
	wxTreeItemId tPluginItem;
	const muhkuh_plugin_desc *ptPluginDesc;
	wxString strName;
	wxString strId;
	wxString strVersion;
	long lItemIdx;
	pluginTreeItemData *ptData;


	// append all plugins to the root item
	tRootItem = m_pluginTree->GetRootItem();

	/* get the plugin description */
	fPluginIsOk = m_ptPluginManager->IsOk(lIdx);
	ptPluginDesc = m_ptPluginManager->getPluginDescription(lIdx);
	if( ptPluginDesc==NULL )
	{
		wxLogError(_("failed to get plugin description!"));
	}
	else
	{
		strName = m_ptPluginManager->GetConfigName(lIdx);

		// create the new data item
		ptData = new pluginTreeItemData(lIdx);

		if( fPluginIsOk==true )
		{
			strId = ptPluginDesc->strPluginId;
			strVersion.Printf(wxT("V%d.%d.%d"), ptPluginDesc->tVersion.uiVersionMajor, ptPluginDesc->tVersion.uiVersionMinor, ptPluginDesc->tVersion.uiVersionSub);

			// set the plugin item
			tPluginItem = m_pluginTree->AppendItem(tRootItem, strName, -1, -1, ptData);
			m_pluginTree->AppendItem(tPluginItem, strId, 3);
			m_pluginTree->AppendItem(tPluginItem, strVersion, 4);
			ShowPluginImage(tPluginItem);
		}
		else
		{
			tPluginItem = m_pluginTree->AppendItem(tRootItem, strName, 2, -1, ptData);
			// append the errormessage
			m_pluginTree->AppendItem(tPluginItem, m_ptPluginManager->GetInitError(lIdx), 2, -1, NULL);
		}
	}
}


void muhkuh_configDialog::ShowPluginImage(wxTreeItemId tPluginItem)
{
	pluginTreeItemData *ptData;
	long lIdx;
	int iImageIdx;


	// get the tree item data
	if( tPluginItem.IsOk()==true )
	{
		ptData = (pluginTreeItemData*)m_pluginTree->GetItemData(tPluginItem);
		if( ptData!=NULL )
		{
			lIdx = ptData->GetPluginId();

			if( m_ptPluginManager->IsOk(lIdx)==false )
			{
				iImageIdx = 2;
			}
			else if( m_ptPluginManager->GetEnable(lIdx)==false )
			{
				iImageIdx = 0;
			}
			else
			{
				iImageIdx = 1;
			}
			m_pluginTree->SetItemImage(tPluginItem, iImageIdx);
		}
	}
}

