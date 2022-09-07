function createAltar(loc, spawn_id)
  if(!loc)
    return;
  endif

  var item := CreateItemAtLocation(loc.x, loc.y, loc.z, "champaltar", 1,loc.realm);
  sleepms(500);

  if(item)
    var items := ListItemsNearLocationOfType( loc.x, loc.y, loc.z, 2, 0x9101, loc.realm);
    foreach pent in items
      SetObjProperty(pent, "spawn", CInt(spawn_id));
    endforeach;
  else
    Print("Error creating item: " + item);
  endif
endfunction

function ActivateAltar(altar)
  var pentagram := GetObjProperty(altar, "pentagram");

  foreach piece in pentagram
    piece:=SystemFindObjectBySerial(piece);
    piece.invisible:=0;
    piece.color:=0;
  endforeach

  SetObjProperty(altar, "active", 1);
  SetObjProperty(altar, "players", dictionary);
endfunction

function DeactivateAltar(altar)
  var pentagram := GetObjProperty(altar, "pentagram");

  foreach piece in pentagram
    piece:=SystemFindObjectBySerial(piece);
    piece.color:=980;
    piece.invisible:=1;
  endforeach

  var activationTime := POLCORE().systime+ACTIVE_EACH+RandomInt(ACTIVE_EACH_RANDOM);

  SetObjProperty(altar, "NextActiv", activationTime);
  EraseObjProperty(altar, "#completed");
  EraseObjProperty(altar, "active");
  EraseObjProperty(altar, "champ");
endfunction
