// Linux implementation of file dialogs

#include "AEngine/Application/FileDialogs.hpp"

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <gtk/gtk.h>

#include <sstream>

namespace aengine
{
    GLFWwindow* FileDialog::window = nullptr;

    std::string FileDialog::OpenFile(const Filter& filter)
    {
        GtkWidget* dialog = gtk_file_chooser_dialog_new("Open", nullptr,
                                                        GTK_FILE_CHOOSER_ACTION_OPEN, 
                                                        "Cancel", GTK_RESPONSE_CANCEL,
                                                        "Open", GTK_RESPONSE_ACCEPT, nullptr);

        gint res = gtk_dialog_run(GTK_DIALOG(dialog));
        if (res == GTK_RESPONSE_ACCEPT)
        {
            std::ostringstream oss;
            
            GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);
            oss << gtk_file_chooser_get_filename(chooser);

            gtk_widget_destroy(dialog);

            return oss.str();
        }

        gtk_widget_destroy(dialog);

        return std::string();
    }

    std::string FileDialog::SaveFile(const Filter& filter)
    {
        return std::string();
    }

    std::string FileDialog::BrowseFolder()
    {
        return std::string();
    }
}
