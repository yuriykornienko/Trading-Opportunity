#include <iostream>
#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;

int wain();

[STAThreadAttribute]
int main(cli::array<System::String^>^ args)
{
    wain();
    
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    proekt3::MyForm form;
    Application::Run(% form);
    
    return 0;
}

