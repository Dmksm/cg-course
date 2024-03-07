#include "stdafx.h"
#include "OpacityDialog.h"
#include "BufferedBitmap.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    BufferedBitmap *m_staticBitmap;
    wxStaticText *m_textView;
    wxImage m_image;

    void OnOpenImage(wxCommandEvent& event);
    void OnChangeOpacity(wxCommandEvent& event);
    void UpdateBitmapImage(const wxImage& image);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MyFrame *frame = new MyFrame("Task 1", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    auto sizer = new wxBoxSizer(wxVERTICAL);

    m_staticBitmap = new BufferedBitmap(this, wxID_ANY, wxBitmap(wxSize(1, 1)),
        wxDefaultPosition, FromDIP(wxSize(500, 200)));
    m_staticBitmap->SetDoubleBuffered(true);
    m_staticBitmap->SetBackgroundColour(*wxRED);

    auto imageButton = new wxButton(this, wxID_ANY, "Load image");
    auto opacityButton = new wxButton(this, wxID_ANY, "Change opacity");

    imageButton->Bind(wxEVT_BUTTON, &MyFrame::OnOpenImage, this);
    opacityButton->Bind(wxEVT_BUTTON, &MyFrame::OnChangeOpacity, this);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(imageButton, 0, wxLEFT, FromDIP(5));
    buttonSizer->Add(opacityButton, 0, wxLEFT, FromDIP(5));

    sizer->Add(buttonSizer, 0, wxCENTER | wxTOP, FromDIP(10));
    sizer->Add(m_staticBitmap, 1, wxEXPAND | wxALL, FromDIP(10));

    this->SetSizerAndFit(sizer);
}

void MyFrame::OnOpenImage(wxCommandEvent& event)
{
    wxFileDialog dialog(this, "Open Image File", "", "",
        "Image Files (*.png;*.jpg;*.jpeg;*.bmp)|*.png;*.jpg;*.jpeg;*.bmp",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );

    if (dialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    if (!m_image.LoadFile(dialog.GetPath()))
    {
        wxMessageBox("Failed to load image file", "Error", wxOK | wxICON_ERROR);
        return;
    }

    if (!m_image.HasAlpha())
    {
        m_image.InitAlpha();
    }

    UpdateBitmapImage(m_image);
}

void MyFrame::OnChangeOpacity(wxCommandEvent& event)
{
    if (!m_image.IsOk())
    {
        wxMessageBox("Please load an image first", "Error", wxOK | wxICON_ERROR);
    }
    else
    {
        OpacityDialog dialog(this);

        if (dialog.ShowModal() == wxID_OK)
        {
            int opacity = dialog.GetSelectedOpacity();
            for (int x = 0; x < m_image.GetWidth(); x++)
            {
                for (int y = 0; y < m_image.GetHeight(); y++)
                {
                    m_image.SetAlpha(x, y, opacity);
                }
            }
        }

        UpdateBitmapImage(m_image);
    }
}

void MyFrame::UpdateBitmapImage(const wxImage& image)
{
    m_staticBitmap->SetBitmap(wxBitmap(image));
}