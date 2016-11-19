Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"CLIC"
    clock:10
    play-mode:"FORCE"
Images:
    ?ImageList(string)<"%s.png">{1-9}:
Groups:
    @main
        ?content(int)<%s>{8-0}:
Animation:
    ?AnimationCode(string):
        "PLAY_GROUP(main, 1)"
        "CALL('HOLD')"