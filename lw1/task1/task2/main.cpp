#include "stdafx.h"
#include "house.h"
//для рисования домика вынести в класс чтобы легко можно было разных размеров домики добавлять
//использовать трансформ
class MyCanvas : public wxPanel
{
public:
    MyCanvas(wxFrame* parent) : wxPanel(parent)
    {
        SetBackgroundColour(*wxWHITE);
        Bind(wxEVT_PAINT, &MyCanvas::OnPaint, this);
        Bind(wxEVT_LEFT_DOWN, &MyCanvas::OnLeftDown, this);
        Bind(wxEVT_LEFT_UP, &MyCanvas::OnLeftUp, this);
        Bind(wxEVT_MOTION, &MyCanvas::OnMouseMove, this);
    }

private:
    void OnPaint(wxPaintEvent& event)
    {
        wxPaintDC dc(this);
        for (auto it : m_houses)
        {
            it.Render(dc);
        }
    }

    void OnLeftDown(wxMouseEvent& event) 
    {
        wxPoint pos = event.GetPosition();
        size_t index = 0;
        for (auto it : m_houses)
        {
            if (it.IsInsideHouse(pos))
            {
                m_currHouseIndex = index;
                m_dragging = true;
                m_dragStart = pos;
                break;
            }
            index++;
        }
    }

    void OnLeftUp(wxMouseEvent& event) 
    {
        m_dragging = false;
    }

    void OnMouseMove(wxMouseEvent& event) 
    {
        if (m_dragging) 
        {
            wxPoint newPos = event.GetPosition();
            int dx = newPos.x - m_dragStart.x;
            int dy = newPos.y - m_dragStart.y;
            auto& it = m_houses.at(m_currHouseIndex);
            wxPoint leftTop = it.GetLeftTopPoint();
            leftTop.x += dx;
            if (leftTop.x < 0)
            {
                leftTop.x = 0;
            }
            if (leftTop.x > 1900 - it.GetWidth())
            {
                leftTop.x = 1900 - it.GetWidth();
            }

            leftTop.y += dy;
            if (leftTop.y < 0)
            {
                leftTop.y = 0;
            }
            if (leftTop.y > 1000 - it.GetHeight())
            {
                leftTop.y = 1000 - it.GetHeight();
            }
            it.Change(leftTop, it.GetWidth(), it.GetHeight());
            m_dragStart = newPos;
            Refresh();
        }
    }

private:
    size_t m_currHouseIndex = 0;
    std::vector<House> m_houses = {
        House({200, 200}, 1000, 700),
        House({20, 20}, 100, 70)
    };
    wxPoint m_dragStart;
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
