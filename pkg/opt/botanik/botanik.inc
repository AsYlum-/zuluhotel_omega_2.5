use uo;


function counttree(leaves)

  var treecount:=0,cfg:=readconfigfile("tree"),restype:=0;

  foreach item in listitemsnearlocation(cint(leaves.x),cint(leaves.y),cint(leaves.z),3)
    restype:=cfg[item.objtype].product;
    if (restype) treecount:=treecount+1; endif
  endforeach

  return treecount;

endfunction

function fixtree(tree,regrow,amt,PlacedBy)
	setobjproperty(tree,"amt",amt);
	setobjproperty(tree,"death",0);
	setobjproperty(tree,"PlacedBy",PlacedBy);
	tree.movable := 0;
	start_script("regrow",{tree,regrow,PlacedBy});
endfunction

function DestroyTree(me, tree)
	if (YesNo(me,"Destroy it?")) 
		if(tree.objtype == 0xca8)
			DestroyItem(tree); 
		elseif(tree.objtype == 0xd1e)
			foreach item in listitemsnearlocation(tree.x, tree.y+2, tree.z, 0)
				if(item.objtype == 0xd1b)
					DestroyItem(item); 
				endif
			endforeach
			foreach item in listitemsnearlocation(tree.x, tree.y-2, tree.z, 0)
				if(item.objtype == 0xd1d)
					DestroyItem(item); 
				endif
			endforeach
			DestroyItem(tree); 
		else
			var tribe := readconfigfile("tree");
			foreach item in listitemsnearlocation(tree.x, tree.y, tree.z, 0)
				if(item.objtype == tribe[tree.objtype].treetype)
					DestroyItem(item); 
				endif
			endforeach
			DestroyItem(tree);
		endif
	endif
endfunction
