#include "pandaFramework.h"
#include "pandaSystem.h"

#include "genericAsyncTask.h"
#include "asyncTaskManager.h"

#include "MainWindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    QWidget *qw = w.centralWidget();

    PandaFramework framework;
    framework.open_framework();

    WindowProperties prop;
    framework.get_default_window_props(prop);

    prop.set_parent_window((size_t)qw->winId());

    // cout<<qw->winId()<<endl;

    WindowFramework *window = framework.open_window(prop,0);
    window->setup_trackball();

    // Load the environment model.
    NodePath scene = window->load_model(framework.get_models(), "models/environment");
    // Reparent the model to render.
    scene.reparent_to(window->get_render());
    // Apply scale and position transforms to the model.
    scene.set_scale(0.25f, 0.25f, 0.25f);
    scene.set_pos(-8, 42, 0);

    // this is the main loop
    Thread *current_thread = Thread::get_current_thread();
    while (framework.do_frame(current_thread)) {
        a.processEvents();
    }

    framework.close_framework();

    return 0;
}
