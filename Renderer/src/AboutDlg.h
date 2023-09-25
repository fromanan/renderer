#pragma once

#include "pch.h"

#include "framework.h"
#include "afxdialogex.h"

// CRendererApp message handlers

// CAboutDlg dialog used for App About

class CAboutDlg final : public CDialogEx
{
public:
    CAboutDlg() noexcept;

    // Dialog Data
    #ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
    #endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Implementation
    protected:
    DECLARE_MESSAGE_MAP()
};