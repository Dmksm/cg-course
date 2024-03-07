#include "stdafx.h"
#include "drawer.h"

class MyCanvas : public wxPanel
{
public:
    MyCanvas(wxFrame* parent) : wxPanel(parent)
    {
        SetBackgroundColour(*wxWHITE);
        Bind(wxEVT_PAINT, &MyCanvas::OnPaint, this);
    }

private:
    void OnPaint(wxPaintEvent& event)
    {
        wxPaintDC dc(this);
        DrawCircle(dc);
    }

    void DrawCircle(wxDC& dc)
    {
        Image img{ { m_width, m_height }, m_backgroundColor };
        FillCircle(img, { m_center.x, m_center.y }, m_radius, m_fillColor, m_outlineColor);
        Print(img, dc);
    }

private:
    wxPoint m_center = { 200, 200 };
    int m_radius = 40;
    unsigned long m_backgroundColor = 0;
    unsigned long m_outlineColor = 255 * pow(256, 2);
    unsigned long m_fillColor = 255;
    int m_height = 300;
    int m_width = 400;
};

class MyFrame : public wxFrame
{
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Drawing Circle", wxDefaultPosition, wxSize(1900, 1000))
    {
        m_canvas = new MyCanvas(this);
        SetBackgroundColour(*wxWHITE);
    }

private:
    MyCanvas* m_canvas;
};

class MyApp : public wxApp
{
public:
    bool OnInit() override
    {
        MyFrame* frame = new MyFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
