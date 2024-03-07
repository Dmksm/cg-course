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
    void OnCreateImage(wxCommandEvent& event);
    void OnSaveImage(wxCommandEvent& event);
    void OnChangeColor(wxCommandEvent& event);

    void UpdateBitmapImage(const wxImage& image);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MyFrame *frame = new MyFrame("Task 2", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    auto sizer = new wxBoxSizer(wxVERTICAL);

    auto imageButton = new wxButton(this, wxID_ANY, "Load image");
    auto saveButton = new wxButton(this, wxID_ANY, "Save as");
    auto createButton = new wxButton(this, wxID_ANY, "New");
    auto colorButton = new wxButton(this, wxID_ANY, "Change color");

    m_staticBitmap = new BufferedBitmap(this, wxID_ANY, wxBitmap(wxSize(1, 1)),
        wxDefaultPosition, FromDIP(wxSize(500, 200)));
    m_staticBitmap->SetDoubleBuffered(true); 
    m_staticBitmap->SetBackgroundColour(*wxBLACK);

    imageButton->Bind(wxEVT_BUTTON, &MyFrame::OnOpenImage, this);
    colorButton->Bind(wxEVT_BUTTON, &MyFrame::OnChangeColor, this);
    createButton->Bind(wxEVT_BUTTON, &MyFrame::OnCreateImage, this);
    saveButton->Bind(wxEVT_BUTTON, &MyFrame::OnSaveImage, this);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(imageButton, 0, wxLEFT, FromDIP(5));
    buttonSizer->Add(saveButton, 0, wxLEFT, FromDIP(5));
    buttonSizer->Add(createButton, 0, wxLEFT, FromDIP(5));
    buttonSizer->Add(colorButton, 0, wxLEFT, FromDIP(5));

    sizer->Add(buttonSizer, 0, wxCENTER | wxTOP, FromDIP(10));
    sizer->Add(m_staticBitmap, 1, wxEXPAND | wxALL, FromDIP(10));

    this->SetSizerAndFit(sizer);
}

void MyFrame::OnChangeColor(wxCommandEvent& event)
{
    wxColourData data;
    data.SetColour(this->GetBackgroundColour());
    wxColourDialog dialog(this, &data);

    if (dialog.ShowModal() == wxID_OK)
    {
        auto color = dialog.GetColourData().GetColour();
        m_staticBitmap->SetColor(color);
        this->Refresh();
    }
}

void MyFrame::OnSaveImage(wxCommandEvent& event)
{
    m_staticBitmap->SaveBitmap();
}

void MyFrame::OnCreateImage(wxCommandEvent& event)
{
    wxSize currSize = m_staticBitmap->GetSize();
    wxImage img;
    img.Create(currSize);
    UpdateBitmapImage(img);
}

void MyFrame::OnOpenImage(wxCommandEvent& event)
{
    wxFileDialog dialog(this, "Open Image File", "", "",
        "Image Files (*.png;*.jpeg;*.bmp)|*.png;*.jpeg;*.bmp",
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

    UpdateBitmapImage(m_image);
}

void MyFrame::UpdateBitmapImage(const wxImage& image)
{
    m_staticBitmap->SetBitmap(wxBitmap(image));
}