Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"FLYKICK_LEFT"
    play-mode:"FORCE"
    clock:50
Images:
    ?ImageList(str)<"0%s.png">{275-278}:
Groups:
    @main
        ?content(int)<%s>{0-3}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(main, 1)"