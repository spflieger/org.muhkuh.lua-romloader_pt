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


#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/imaglist.h>
#include <wx/textctrl.h>
#include <wx/treebook.h>
#include <wx/treectrl.h>


#ifndef __MUHKUH_CONFIGDIALOG_H__
#define __MUHKUH_CONFIGDIALOG_H__

#include "muhkuh_plugin_manager.h"
#include "muhkuh_repository_manager.h"


class pluginTreeItemData : public wxTreeItemData
{
public:
	pluginTreeItemData(long lPluginId)
	 : m_lPluginId(lPluginId)
	 { };

	long GetPluginId(void) const
	{
		return m_lPluginId;
	};

private:
	long m_lPluginId;
};


class repositoryTreeItemData : public wxTreeItemData
{
public:
	repositoryTreeItemData(long lRepositoryId)
	 : m_lRepositoryId(lRepositoryId)
	 { };

	long GetRepositoryId(void) const
	{
		return m_lRepositoryId;
	};

private:
	long m_lRepositoryId;
};


class muhkuh_configDialog : public wxDialog
{
public:
	muhkuh_configDialog(wxWindow *parent, const wxString strApplicationPath, muhkuh_plugin_manager *ptPluginManager, muhkuh_repository_manager *ptRepositoryManager);

	void OnNewRepositoryButton(wxCommandEvent &event);
	void OnEditRepositoryButton(wxCommandEvent &event);
	void OnDeleteRepositoryButton(wxCommandEvent &event);
	void OnRepositorySelect(wxTreeEvent &event);

	void OnAddPluginButton(wxCommandEvent &event);
	void OnRemovePluginButton(wxCommandEvent &event);
	void OnEnablePluginButton(wxCommandEvent &event);
	void OnDisablePluginButton(wxCommandEvent &event);
	void OnPluginSelectionChanged(wxTreeEvent &event);
	void OnPluginSelectionChanging(wxTreeEvent &event);

private:
	void createControls(void);
	wxPanel *createControls_repository(wxWindow *ptParent);
	wxPanel *createControls_plugin(wxWindow *ptParent);

	void ShowNewRepository(long lIdx);
	void ShowNewPlugin(long lIdx);

	void ShowPluginImage(wxTreeItemId tPluginItem);

	void SetPluginButtons(wxTreeItemId tItem);

	muhkuh_repository_manager *m_ptRepositoryManager;
	muhkuh_plugin_manager *m_ptPluginManager;

	wxString m_strApplicationPath;

	// the controls
	wxTreebook *m_treeBook;
	wxTreeCtrl *m_repositoryTree;
	wxTreeCtrl *m_pluginTree;
	wxBoxSizer *m_buttonSizer;
	wxToolBar *m_repositoryToolBar;
	wxToolBar *m_pluginToolBar;
	wxButton *m_buttonOk;
	wxButton *m_buttonCancel;

    DECLARE_EVENT_TABLE()
};




#endif	// __MUHKUH_CONFIGDIALOG_H__
