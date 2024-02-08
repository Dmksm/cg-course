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
        Image img{ { m_width, m_height }, 255};
        FillCircle(img, { m_center.x, m_center.y }, 2, 25);
        Print(img, dc);
    }

private:
    wxPoint m_center = { 200, 200 };
    wxPoint m_dragStart;
    int m_height = 700;
    int m_width = 1000;
    bool m_dragging = false;
};

class MyFrame : public wxFrame
{
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Draggable House", wxDefaultPosition, wxSize(1900, 1000))
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
