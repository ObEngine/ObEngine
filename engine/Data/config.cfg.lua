mode "Settings"

configuration {
    antiAliasing = true,
    scrollSensibility = 1,
    framerateLimit = true,
    framerateTarget = 60,
    vsync = true
}

keybinding {
    mapEditor = context {
        SpriteMode = input { Pressed "1" },
        CollisionMode = input { Pressed "2" },
        CamMovable = input { Pressed "F10" },
        CamFree = input { Pressed "F11" },
        CamUp = input { Hold "Z" },
        CamDown = input { Hold "S" + Idle "LControl" },
        CamLeft = input { Hold "Q" },
        CamRight = input { Hold "D"}
    }
}

debug {
    logLevel = LogLevel.debug
}