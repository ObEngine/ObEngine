Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"STAND_RIGHT"
    play-mode:"FORCE"
    clock:70
Images:
    ?ImageList(str)<"00%s.png">{13-14}:
Groups:
    @main
        ?content(int)<%s>{0-1}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(main, 1)"
        "CALL('IDLE_LEFT')"