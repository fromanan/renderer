// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
public:
    CMainFrame() noexcept;

protected:
    DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:
// Operations
public:
// Overrides
public:
    BOOL PreCreateWindow(CREATESTRUCT& cs) override;
    BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) override;

// Implementation
public:
    ~CMainFrame() override;
    #ifdef _DEBUG
    void AssertValid() const override;
    void Dump(CDumpContext& dc) const override;
    #endif

// control bar embedded members
protected: 
    CToolBar m_wndToolBar;
    CStatusBar m_wndStatusBar;
    CChildView m_wndView;

// Generated message map functions
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    DECLARE_MESSAGE_MAP()
};
