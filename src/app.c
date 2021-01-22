#include "app.h"

internal void UpdateApp(platform *platform)
{
    Assert(sizeof(app_state) <= platform->storage_size);

    app_state *state = (app_state *)platform->storage;
    if (!platform->initialized)
    {

        memory->initialized = 1;
    }
}
