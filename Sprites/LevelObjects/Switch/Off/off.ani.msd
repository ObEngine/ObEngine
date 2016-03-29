Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"Off"
    clock:1000
Images:
    ?ImageList(str)<"off.png">{0}:
Groups:
    @main
        ?content(int)<%s>{0}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(main, -1)"