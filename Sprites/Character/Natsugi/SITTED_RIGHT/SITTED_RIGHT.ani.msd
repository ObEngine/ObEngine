Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"SITTED_RIGHT"
    clock:70
Images:
    ?ImageList(str):
        "0009.png"
        "0010.png"
        "0011.png"
        "0012.png"
Groups:
    @main
        ?content(int)<%s>{0-3}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(main, -1)"