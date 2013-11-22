if(typeof Deki == "undefined")
{
	var Deki = {};
}

Deki.nav = function()
{
	var selectedNode, prevSelectedNode, selectedChildren, timeout;

	//Toggle debug console on/off
	var debug = false;

	//Nav wrapper ID
	var navDivID = "siteNavTree";

	//Animation speed (seconds)
	var animOpenCloseSpeed = 0.15;			// expand, collapse child & hidden nodes
	var animChangeBackgroundSpeed = 0;		// switch background color of selected node
	var animImagePadSpeed = 0; // 0.04;
	var animShiftSpeed = 0.1;

	//Time before redirect occurs (millisec)
	var redirectTime = 0;
	var redirectDelay = 0; // 1500

	//Toggle redirect on/off
	var redirect = true;

	//Max text width in nav pane
	var maxWidth = 0;

	//RGB values (auto detected from css)
	var siblingRGB, dockedNodeRGB, selectedRGB, selectedChildRGB;

	//Width and padding properties
	var properties = {};

	return {
		//Initialize navigation
		init: function()
		{
			//Initialize properties
			Deki.nav.initProperties();

			//Initialize hover
			Deki.nav.initHover();

			Deki.nav.maxWidth = navMaxWidth;

			//Initialize click
			Deki.nav.initClick();
		},

		//Initialize properties
		initProperties: function()
		{
			YAHOO.util.Event.onContentReady(navDivID,
				function()
				{
					//------------------------Determine background colors--------------------

					var testClasses = ["sibling", "dockedNode", "selected", "selectedChild"];

					//Create invisible test node
					Deki.$("#" + navDivID).append("<div id='testNode' class='node' style='display:none'><a></a></div>");

					for(var i = 0; i < testClasses.length; i++)
					{
						var testClass = testClasses[i];

						//Add class to test node
						Deki.$("#testNode").addClass(testClass);

						//Get background color
						var color = Deki.$("#testNode a").css("backgroundColor")
						if(color && (color.toLowerCase() != 'transparent')) {

							//Get color as RGB
							var rgb = new RGBColor(color).toRGB();

							//Set global color variable to RGB
							eval(testClass + "RGB = '" + rgb + "';");
						}

						//Remove class from test node
						Deki.$("#testNode").removeClass(testClass);
					}

					//--------------------------Determine padding and width-----------------------

					properties.linkWidth 		= parseInt(Deki.$("#testNode a").css("width"));
					properties.linkHeight 		= parseInt(Deki.$("#testNode a").css("height")) + parseInt(Deki.$("#testNode a").css("borderBottomWidth"));
					properties.linkPadLeft 		= parseInt(Deki.$("#testNode a").css("paddingLeft"));
					properties.linkPadRight 	= parseInt(Deki.$("#testNode a").css("paddingRight"));
					properties.imgPadRight 		= parseInt(Deki.$("#testNode img.nodeImage").css("paddingRight"));

					Deki.$("#testNode").addClass("selectedChild");

					properties.selChildPadLeft 	= parseInt(Deki.$("#testNode a").css("paddingLeft"));
					properties.selChildPadRight = parseInt(Deki.$("#testNode a").css("paddingRight"));
					properties.selChildWidth 	= parseInt(Deki.$("#testNode a").css("width"));

					Deki.$("#testNode").removeClass("selectedChild").addClass("sibling");

					properties.sibImgPadLeft 	= parseInt(Deki.$("#testNode img.nodeImage").css("paddingLeft"));
					properties.sibImgPadRight 	= parseInt(Deki.$("#testNode img.nodeImage").css("paddingRight"));

					//Remove test node
					Deki.$("#testNode").remove();
				}
			);
		},

		//Initialize hover
		initHover: function()
		{
			//Get child nodes that are not closed
			var childNodes = Deki.$("#" + navDivID + " div.childNode").not(".closedNode").get();

			//Add mouseover listener
			YAHOO.util.Event.addListener(childNodes, "mouseover", Deki.nav.mouseover);

			//Add mouseout listener
			YAHOO.util.Event.addListener(childNodes, "mouseout", Deki.nav.mouseout);

			//----------Debug----------

			if(debug)
			{
				if(!YAHOO.util.Dom.inDocument("navDebug"))
				{
					Deki.$(document.body).append("<div id='navDebug' style='width: 400px; height: 50px; z-index: 2; padding: 10px; background: white; border: 1px solid #666; position:absolute; left: 200px; top: 200px;'></div>");
				}

				YAHOO.util.Event.addListener(Deki.$("div.node"), "mouseover",
					function()
					{
						Deki.$("#navDebug").html(this.className);
					}
				);

				YAHOO.util.Event.addListener(Deki.$("div.node"), "mouseout",
					function()
					{
						Deki.$("#navDebug").html("");
					}
				);
			}
		},

		//Remove hover
		removeHover: function()
		{
			var nodes = Deki.$("#" + navDivID + " div.node").get();

			//Remove listeners
			YAHOO.util.Event.removeListener(nodes, "mouseover");
			YAHOO.util.Event.removeListener(nodes, "mouseout");
		},

		//Reset hover
		resetHover: function()
		{
			Deki.nav.removeHover();
			Deki.nav.initHover();
		},

		//Initialize click
		initClick: function()
		{
			var nodes = Deki.$("#" + navDivID + " div.node");
			nodes.attr("onclick", "return false;");

			//Add click handler
			YAHOO.util.Event.addListener(nodes.get(), "click", Deki.nav.click);
		},

		//Remove click
		removeClick: function()
		{
			var nodes = Deki.$("#" + navDivID + " div.node");
			nodes.attr("onclick", "");

			//Add click handler
			YAHOO.util.Event.removeListener(nodes.get(), "click", Deki.nav.click);
		},

		//Reset click
		resetClick: function()
		{
			Deki.nav.removeClick();
			Deki.nav.initClick();
		},

		//Reset all handlers
		resetAllHandlers: function()
		{
			//Initialize click
			Deki.nav.resetClick();

			//Reset hover
			Deki.nav.resetHover();
		},

		//Mouseover
		mouseover: function()
		{
		},

		//Mouseout
		mouseout: function()
		{
		},

		//Click
		click: function(ev)
		{
			//Redirect turned on
			redirect = true;

			//Get previously selected node
			prevSelectedNode = Deki.$("#" + navDivID + " div.selected").get(0);

			//Currently selected node
			selectedNode = this;

			//Exit if clicked node is already the current node
			if(YAHOO.util.Dom.hasClass(selectedNode, "selected") || (Deki.$(selectedNode).attr("reload") == "1"))
			{
				redirectTime = 0;
				// cancel the default click event
				// @see #MT-9745
				YAHOO.util.Event.stopEvent(ev);
				Deki.nav.animComplete();
				return false;
			}

			//Hidden nodes
			if(YAHOO.util.Dom.hasClass(selectedNode, "moreNodes"))
			{
				Deki.nav.hiddenNodes.startAnim();
				return;
			}

			//Clear timeout if running
			if(timeout)
			{
				window.clearTimeout(timeout);
			}

			//Automatic redirect if node has no children
			if(	(!YAHOO.util.Dom.hasClass(selectedNode, "parentOpen") && !YAHOO.util.Dom.hasClass(selectedNode, "parentClosed")) )
			{
				redirectTime = 0;
			}
			else
			{
				redirectTime = redirectDelay;
			}

			// cancel the default click event
			// @see #0002049
			YAHOO.util.Event.stopEvent(ev);

			//Get missing data, animate, redirect
			Deki.nav.getData();
		},

		animComplete: function()
		{
			//Reset Hover
			Deki.nav.resetHover();

			if(selectedNode)
			{
				Deki.$(selectedNode).find("a").css("backgroundColor", "");
			}

			if(prevSelectedNode)
			{
				Deki.$(prevSelectedNode).find("a").css("backgroundColor", "");
			}

			//Start timer
			var disableNavWhenEditorIsLoaded = false;
			if(redirect && ((Deki.$(selectedNode).attr("reload") == "1") || !(disableNavWhenEditorIsLoaded && Deki.EditorInstance && Deki.EditorInstance.IsStarted())))
			{
				timeout = window.setTimeout(Deki.nav.redirect, redirectTime);
			}
		},

		redirect: function()
		{
			// Opera doesn't support onbeforeunload event
			if ( YAHOO.env.ua.opera && Deki.EditorInstance && !Deki.EditorInstance.ConfirmCancel() )
			{
				return false;
			}

			var path = Deki.$(selectedNode).find("a").attr("href");

			// SteveB: remove click handlers (which restores the default 'href' behavior)
			Deki.nav.removeClick();

			if(!path)
			{
				path = "";
			}
			// fix for IE6 when canceling page redirect
			try
			{
				window.location = path;
			}
			catch(e) {}
		},

		//Get missing nodes
		getData: function()
		{
			var allChildren		= false;
			var partialChildren	= false;
			var allSiblings		= false;
			var request 		= [];
			var selChildData 	= Deki.$(selectedNode).attr("cd") || "1";		// children-data (0=data missing, nXYZ=known child)
			var selSiblingData 	= Deki.$(selectedNode).attr("sd") || "1";		// sibling-data (0=data missing)
			var knownChild		= null;
			var exclude			= "";

			if(matchResult = selChildData.match(new RegExp("n([0-9]+)")))
			{
				knownChild = matchResult[0];
			}

			//Child data
			if(selChildData == "0")
			{
				allChildren = true;
				request.push("children");
			}
			else if(knownChild)
			{
				partialChildren = true;
				request.push("children");

				exclude = "&exclude=" + knownChild.replace(new RegExp("n"), "");
			}

			//Sibling data
			if(selSiblingData == "0")
			{
				allSiblings = true;
				request.push("siblings");
			}

			//Ajax call for missing nodes
			if(request.length)
			{
				var nodeID = Deki.$(selectedNode).attr("id").replace(new RegExp("^n"), "");
		        var scheme = window.location.protocol.replace(/:.*/, '');
		        var requestURL = "/@api/deki/site/nav/" + nodeID + "/" + request.join(",") + "?dream.in.scheme=" + scheme + "&dream.out.format=json" + exclude;
        		if(Deki.nav.maxWidth > 0)
				{
					requestURL = requestURL + "&width=" + Deki.nav.maxWidth;
				}

				//Debug
				//Deki.$(document.body).append(requestURL);

				YAHOO.util.Connect.asyncRequest(
					"GET",
					requestURL,
					{
						success: function(obj)
						{
							//Evaluate response
							eval("var response = " + obj.responseText);

							//Children data
							if(response.children)
							{
								var childData 	= response.children.html;
								var childNodes	= response.children.nodes;
							}

							//Sibling data
							if(response.siblings)
							{
								var siblingData 	= response.siblings.html;
								var siblingNodes	= response.siblings.nodes;
							}

							//-------------Add children------------

							//All children
							if(allChildren)
							{
								//Set list of child node IDs
								Deki.$(selectedNode).attr("c", childNodes);

								//Append children
								Deki.$(selectedNode).after(childData);
							}
							//Partial children
							else if(partialChildren)
							{
								//Set list of child node IDs
								Deki.$(selectedNode).attr("c", childNodes);

								//Prepend siblings
								if(childData.pre)
								{
									Deki.$("#" + knownChild).before(childData.pre);
								}

								//Append siblings
								if(childData.post)
								{
									Deki.$(Deki.nav.getLastChild(
											Deki.$("#" + knownChild).get()
										)
									).after(childData.post);
								}

								//All children of the selected node have full sibling knowledge
								Deki.$(
									Deki.nav.common.getNodesFromAttr(selectedNode, "c")
								).attr("sd", "");
							}

							//------------Add siblings-----------

							if(allSiblings)
							{
								//Prepend siblings
								if(siblingData.pre)
								{
									Deki.$(selectedNode).before(siblingData.pre);
								}

								//Append siblings
								if(siblingData.post)
								{
									Deki.$(Deki.nav.getLastChild(selectedNode)).after(siblingData.post);
								}

								//Parent node has full child data
								Deki.$("#" + Deki.$(selectedNode).attr("p")).attr("cd", "").attr("c", siblingNodes);
							}

							//Update data states of selected node
							Deki.$(selectedNode).attr("cd", "").attr("sd", "");

							//Re-initialize event handlers
							Deki.nav.resetAllHandlers();

							//Start animation
							Deki.nav.startAnim();
						}
					}
				);
			}
			else
			{
				//Start animation
				Deki.nav.startAnim();
			}
		},

		//Get last child of node
		getLastChild: function(node)
		{
			var childNodes;

			while(true)
			{
				childNodes = Deki.$(node).attr("c");

				if(childNodes)
				{
					childNodes 	= childNodes.split(",");
					node 		= Deki.$("#" + childNodes[childNodes.length - 1]).get(0);
				}
				else
				{
					break;
				}
			}

			return node;
		},

		//Start animation
		startAnim: function()
		{
			selectedChildren = null;

			//Get children of selected node
			if(YAHOO.util.Dom.hasClass(selectedNode, "parentClosed"))
			{
				selectedChildren = Deki.nav.common.getNodesFromAttr(selectedNode, "c");
			}

			//Sibling
			if(YAHOO.util.Dom.hasClass(selectedNode, "sibling"))
			{
				Deki.nav.sibling.startAnim();
			}
			//Child node
			else if(YAHOO.util.Dom.hasClass(selectedNode, "selectedChild"))
			{
				Deki.nav.child.startAnim();
			}
			//Home node
			else if(YAHOO.util.Dom.hasClass(selectedNode, "homeNode"))
			{
				Deki.nav.docked.homeNode.startAnim();
			}
			//Last docked
			else if(YAHOO.util.Dom.hasClass(selectedNode, "lastDocked"))
			{
				Deki.nav.docked.lastDocked.startAnim();
			}
			//Mid docked
			else
			{
				Deki.nav.docked.midDocked.startAnim();
			}
		},

		//-------------------------------Common--------------------------------

		common:
		{
			//Complete function handler
			onComplete: function(anim, completeFuncs)
			{
				if(completeFuncs)
				{
					if(completeFuncs.length)
					{
					    for (var i=0; i<completeFuncs.length; i++)
					    {
					        if (typeof(completeFuncs[i]) == 'undefined')
					        {
					            continue;
					        }

							if(anim)
							{
								anim.onComplete.subscribe(
									completeFuncs[i]
								);
							}
							else
							{
								completeFuncs[i]();
							}
						}
					}
					else
					{
						if(anim)
						{
							anim.onComplete.subscribe(completeFuncs);
						}
						else
						{
							completeFuncs();
						}
					}
				}
			},

			//Compact nodes
			compactNodes: function(nodes, completeFuncs)
			{
				var anim = new YAHOO.util.Anim(
					nodes,
					{height: {to: (YAHOO.env.ua.ie > 0 && YAHOO.env.ua.ie < 7) ? 0.1 : 0}}, //make collapsing sorta of work for IE6
					animOpenCloseSpeed,
					YAHOO.util.Easing.easeIn
				);

				anim.onComplete.subscribe(
					function()
					{
						Deki.$(nodes).addClass("closedNode");
					}
				);

				Deki.nav.common.onComplete(anim, completeFuncs);

				anim.animate();
			},

			//Open nodes
			openNodes: function(nodes, completeFuncs)
			{
				nodes = Deki.$(nodes).not(".hiddenNode");

				Deki.$(nodes).show();

				var anim = new YAHOO.util.Anim(
					nodes,
					{height: {to: properties.linkHeight}},
					animOpenCloseSpeed,
					YAHOO.util.Easing.easeIn
				);

				anim.onComplete.subscribe(
					function()
					{
						Deki.$(nodes).removeClass("closedNode");
					}
				);

				Deki.nav.common.onComplete(anim, completeFuncs);

				anim.animate();
			},

			//Compact image padding
			compactImagePad: function(nodes, completeFuncs)
			{
				if(animImagePadSpeed > 0)
				{
					var anim = new YAHOO.util.Anim(
						Deki.$(nodes).find("img.nodeImage").get(),
						{paddingLeft: {to: 0}, paddingRight: {to: properties.imgPadRight}},
						animImagePadSpeed,
						YAHOO.util.Easing.easeIn
					);

					Deki.nav.common.onComplete(anim, completeFuncs);
					anim.animate();
				}
				else
				{
					Deki.$(nodes).find("img.nodeImage").css("paddingLeft", 0).css("paddingRight", properties.imgPadRight);
					Deki.nav.common.onComplete(null, completeFuncs);
				}
			},

			//Expand image padding
			expandImagePad: function(nodes, completeFuncs)
			{
				if(animImagePadSpeed > 0)
				{
					var anim = new YAHOO.util.Anim(
						Deki.$(nodes).find("img.nodeImage").get(),
						{paddingLeft: {to: properties.sibImgPadLeft}, paddingRight: {to: properties.sibImgPadRight}},
						animImagePadSpeed,
						YAHOO.util.Easing.easeOut
					);

					Deki.nav.common.onComplete(anim, completeFuncs);
					anim.animate();
				}
				else
				{
					Deki.$(nodes).find("img.nodeImage").css("paddingLeft", properties.sibImgPadLeft).css("paddingRight", properties.sibImgPadRight);
					Deki.nav.common.onComplete(null, completeFuncs);
				}
			},

			//Shift nodes to the left
			shiftLeft: function(nodes, completeFuncs)
			{
				var anim = new YAHOO.util.Anim(
					Deki.$(nodes).find("a").get(),
					{paddingLeft: {to: properties.linkPadLeft}, width: {to: properties.linkWidth}},
					animShiftSpeed,
					YAHOO.util.Easing.easeIn
				);

				Deki.nav.common.onComplete(anim, completeFuncs);
				anim.animate();
			},

			//Shift nodes to the right
			shiftRight: function(nodes, completeFuncs)
			{
				var anim = new YAHOO.util.Anim(
					Deki.$(nodes).find("a").get(),
					{paddingLeft: {to: properties.selChildPadLeft}, width: {to: properties.selChildWidth}},
					animShiftSpeed,
					YAHOO.util.Easing.easeOut
				);

				Deki.nav.common.onComplete(anim, completeFuncs);
				anim.animate();
			},

			//Open parent node
			openParent: function(node)
			{
				if(YAHOO.util.Dom.hasClass(node, "parentClosed"))
				{
					Deki.$(node).removeClass("parentClosed").addClass("parentOpen");
				}
			},

			//Close parent node
			closeParent: function(node)
			{
				if(YAHOO.util.Dom.hasClass(node, "parentOpen"))
				{
					Deki.$(node).removeClass("parentOpen").addClass("parentClosed");
				}
			},

			//Get nodes from attribute
			getNodesFromAttr: function(node, attr, ignore)
			{
				var attribute = Deki.$(node).attr(attr);

				if(attribute)
				{
					var list = attribute.split(",");

					// check if there is an element to ignore
					if(ignore)
					{

						// remove the element to ignore
						var i = 0;
						while(i < list.length)
						{
							if (list[i] == ignore)
							{
								list.splice(i, 1);
								break;
							}
							else
							{
								i++;
							}
						}
					}
					return YAHOO.util.Dom.get(list);
				}
				else
				{
					return [ ];
				}
			}
		},

		//----------------------------Debug-----------------------
		debug:
		{
			printIDs: function(nodes)
			{
				var idStr = "";

				Deki.$(nodes).each(
					function()
					{
						idStr += this.id + ", ";
					}
				);

				alert(idStr);
			},

			logClicks: function()
			{
				Deki.$("#clickLog").append(this.id + "<br />");
			}
		},

		//-------------------------------Docked--------------------------------

		docked:
		{
			//---------------------------Home node---------------------------

			homeNode:
			{
				//Start animation
				startAnim: function()
				{
					if(selectedRGB) {
						Deki.$(selectedNode).find("a").css("backgroundColor", selectedRGB);
					}
					if(siblingRGB) {
						Deki.$(prevSelectedNode).find("a").css("backgroundColor", siblingRGB);
					}

					//Unhighlight selected node
					Deki.$(prevSelectedNode).removeClass("selected");

					//Close parent
					Deki.nav.common.closeParent(prevSelectedNode);

					var nodeStr = 'var nodes = Deki.$("div.node").not(".homeNode").not(".closedNode")';

					Deki.$(selectedChildren).each(
						function()
						{
							nodeStr += '.not("#' + this.id + '")';
						}
					);

					nodeStr += ".get()";

					eval(nodeStr);

					//var nodes = Deki.$("div.node").not(".homeNode").not(".closedNode").not(selectedChildren).get();

					if(nodes.length)
					{
						//Strip nodes
						Deki.$(nodes).removeClass("sibling").removeClass("selectedChild").removeClass("dockedNode").removeClass("lastDocked");

						//Close non-child nodes
						Deki.nav.common.compactNodes(
							nodes,
							Deki.nav.docked.homeNode.showChildren
						);
					}
					else
					{
						Deki.nav.docked.homeNode.showChildren();
					}
				},

				//Show children
				showChildren: function()
				{
					var closedNodes = Deki.$(selectedChildren).filter(".closedNode").not(".hiddenNode").get();

					Deki.$(selectedChildren).each(
						function()
						{
							if(YAHOO.util.Dom.hasClass(this, "parentOpen"))
							{
								Deki.nav.common.closeParent(this);
							}
						}
					);

					//Expand image padding
					Deki.nav.common.expandImagePad(selectedChildren);

					Deki.$(selectedChildren).addClass("sibling").addClass("childNode").removeClass("selectedChild").removeClass("dockedNode").removeClass("lastDocked");

					if(closedNodes.length)
					{
						Deki.nav.common.openNodes(
							closedNodes,
							Deki.nav.docked.homeNode.highlightSelected
						);
					}
					else
					{
						Deki.nav.docked.homeNode.highlightSelected();
					}
				},

				//Highlight selected node
				highlightSelected: function()
				{
					Deki.$(selectedNode).addClass("selected");

					//Animation complete
					Deki.nav.animComplete();
				}
			},

			//---------------------------Last Docked---------------------------

			lastDocked:
			{
				//Start animation
				startAnim: function()
				{
					if(selectedRGB) {
						Deki.$(selectedNode).find("a").css("backgroundColor", selectedRGB);
					}
					if(siblingRGB) {
						Deki.$(prevSelectedNode).find("a").css("backgroundColor", siblingRGB);
					}

					var viewableChildren = Deki.$("#" + navDivID + " div.selectedChild").get();

					//Minimize children of previously selected node (if they exist)
					if(viewableChildren.length)
					{
						Deki.nav.common.compactNodes(
							viewableChildren,
							function()
							{
								Deki.$(viewableChildren).removeClass("selectedChild");

								Deki.nav.docked.lastDocked.siblingsToChildren();
							}
						);
					}
					else
					{
						Deki.nav.docked.lastDocked.siblingsToChildren();
					}
				},

				//Transform siblings into children
				siblingsToChildren: function()
				{
					//Close previously selected node
					Deki.nav.common.closeParent(prevSelectedNode);

					//Move siblings to the right
					Deki.nav.common.shiftRight(Deki.$("#" + navDivID + " div.sibling").get(),
						function()
						{
							Deki.$(prevSelectedNode).find("a").css("backgroundColor", "");

							//Minimize node image padding
							Deki.nav.common.compactImagePad(Deki.$("#" + navDivID + " div.sibling"));

							Deki.$("#" + navDivID + " div.sibling").addClass("selectedChild").removeClass("sibling").addClass("childNode");
							Deki.$(prevSelectedNode).removeClass("selected");

							//Highlight selected node
							Deki.nav.docked.highlightSelected();
						}
					);
				}
			},

			//---------------------------Mid Docked---------------------------

			midDocked:
			{
				//Start animation
				startAnim: function()
				{
					if(selectedRGB) {
						Deki.$(selectedNode).find("a").css("backgroundColor", selectedRGB);
					}
					if(siblingRGB) {
						Deki.$(prevSelectedNode).find("a").css("backgroundColor", siblingRGB);
					}

					//Close current child nodes
					Deki.nav.common.compactNodes(
						Deki.$("#" + navDivID + " div.childNode").not(".closedNode").get(),
						function()
						{
							//Unhighlight previously selected node
							Deki.nav.common.closeParent(prevSelectedNode);
							Deki.$(prevSelectedNode).removeClass("selected");

							// remove child & sibling styles
							Deki.$("#" + navDivID + " div.childNode").removeClass("selectedChild").removeClass("sibling");

							//Hide grandchildren and their children
							Deki.nav.docked.midDocked.hideGrandchildren();
						}
					);
				},

				//Hide grandchildren and their children
				hideGrandchildren: function()
				{
					var grandchildren 	= [];
					var selectedPath 	= Deki.$(selectedNode).attr("path");

					Deki.$("#" + navDivID + " div.dockedNode").each(
						function()
						{
							if((new RegExp(selectedPath + "[^/]+/([^/]+/)+$")).test(this.getAttribute("path")))
							{
								grandchildren.push(
									Deki.$("#" + this.id).get(0)
								);
							}
						}
					);

					if(grandchildren.length)
					{
						Deki.nav.common.compactNodes(
							grandchildren,
							function()
							{
								Deki.$(grandchildren).removeClass("dockedNode");

								Deki.nav.docked.midDocked.transformDockedChild();
							}
						);
					}
					else
					{
						Deki.nav.docked.midDocked.transformDockedChild();
					}
				},

				//Transform docked child
				transformDockedChild: function()
				{
					var dockedChild = Deki.$(selectedChildren).filter(".dockedNode").get(0);

					// switch left icon	& style
					Deki.$(dockedChild).removeClass("dockedNode").removeClass("lastDocked").addClass("childNode").addClass("selectedChild");

					//Move docked child to the right
					Deki.nav.common.shiftRight(
						dockedChild,
						function() { }
					);
					Deki.nav.docked.midDocked.showSelectedChildren();
				},

				//Show selected node's children
				showSelectedChildren: function()
				{
					var hiddenChildren = Deki.$(selectedChildren).filter(".closedNode").get();

					//Shift children to the right
					if(hiddenChildren.length)
					{
						Deki.nav.common.shiftRight(
							hiddenChildren,
							function()
							{
								Deki.$(hiddenChildren).addClass("selectedChild");
							}
						);

						//Minimize image padding
						Deki.nav.common.compactImagePad(hiddenChildren);

						//Open nodes
						Deki.nav.common.openNodes(
							hiddenChildren,
							Deki.nav.docked.highlightSelected
						);
					}
					else
					{
						Deki.nav.docked.highlightSelected();
					}
				}
			},

			//---------------------------Common---------------------------

			//Highlight selected node
			highlightSelected: function()
			{
				//Expand node image padding
				Deki.nav.common.expandImagePad(selectedNode);

				//Highlight node
				Deki.$(selectedNode).removeClass("dockedNode").removeClass("lastDocked").
				addClass("sibling").addClass("selected").addClass("childNode");

				//Open node if parent
				Deki.nav.common.openParent(selectedNode);

				//Set parent to last docked
				var parentID = Deki.$(selectedNode).attr("p");
				Deki.$("#" + parentID).addClass("lastDocked");

				//Show siblings
				Deki.nav.docked.showSiblings();
			},

			//Show siblings
			showSiblings: function()
			{
				// fetch parent of current node
				var parentNode = Deki.$("#" + Deki.$(selectedNode).attr("p"));
				if(parentNode)
				{
					// fetch children of parent (i.e. siblings of current node), but remove current node
					var siblings = Deki.nav.common.getNodesFromAttr(parentNode, "c", Deki.$(selectedNode).attr("id"));
					if(siblings && siblings.length)
					{
						Deki.$(siblings).addClass("sibling").addClass("childNode");

						Deki.nav.common.openNodes(siblings,
							function()
							{
								//Animation complete
								Deki.nav.animComplete();
							}
						);
					}
					else
					{
						//Animation complete
						Deki.nav.animComplete();
					}
				}
				else
				{
					//Animation complete
					Deki.nav.animComplete();
				}
			}
		},

		//-------------------------------Child--------------------------------

		child:
		{
			//Start animation
			startAnim: function()
			{
				if(selectedRGB) {
					Deki.$(selectedNode).find("a").css("backgroundColor", selectedRGB);
				}
				if(dockedNodeRGB) {
					Deki.$(prevSelectedNode).find("a").css("backgroundColor", dockedNodeRGB);
				}

				Deki.nav.child.hideSiblings();
			},

			//Hide siblings
			hideSiblings: function()
			{
				var nodes = Deki.$("#" + navDivID + " div.sibling").not(".selected").get();

				if(nodes.length)
				{
					Deki.nav.common.compactNodes(
						nodes,
						function()
						{
							Deki.$("#" + navDivID + " div.sibling").not(".selected").removeClass("sibling");
							Deki.nav.child.unhighlightSelected();
						}
					);
				} else {
					Deki.nav.child.unhighlightSelected();
				}
			},

			//Unhighlight selected
			unhighlightSelected: function()
			{
				//Last docked is no longer last
				Deki.$("#" + navDivID + " div.lastDocked").removeClass("lastDocked");

				//Transform node into docked node
				Deki.$(prevSelectedNode).removeClass("sibling").removeClass("childNode").removeClass("selected").addClass("dockedNode").addClass("lastDocked").find("img.nodeImage");

				// check if we need to close the previous parent
				if(YAHOO.util.Dom.hasClass(prevSelectedNode, "parentOpen"))
				{
					Deki.$(prevSelectedNode).removeClass("parentOpen").addClass("parentClosed");
				}

				//Remove node image padding
				Deki.nav.common.compactImagePad(prevSelectedNode);

				//Expand node image padding
				Deki.nav.common.expandImagePad(
					Deki.$("#" + navDivID + " div.selectedChild")
				);

				//Move to left
				Deki.nav.common.shiftLeft(
					Deki.$("#" + navDivID + " div.selectedChild"),
					function()
					{
						//Change selected children to sibling nodes
						Deki.$("#" + navDivID + " div.selectedChild").removeClass("selectedChild").addClass("sibling");

						Deki.nav.child.highlightSelected();
					}
				);
			},

			//Highlight selected node
			highlightSelected: function()
			{
				//Mark node as selected
				Deki.$(selectedNode).addClass("selected");

				if(YAHOO.util.Dom.hasClass(Deki.$(selectedNode).get(0), "parentClosed"))
				{
					//Open selected node
					Deki.nav.common.openParent(selectedNode);

					//Open children
					Deki.nav.child.openChildren();
				}
				else
				{
					//Animation complete
					Deki.nav.animComplete();
				}
			},

			//Open children
			openChildren: function()
			{
				// shift right
				Deki.$(selectedChildren).find("a").css("paddingLeft", properties.selChildPadLeft).css("width", properties.selChildWidth);

				Deki.nav.common.openNodes(selectedChildren,
					Deki.nav.child.shiftRight
				);
			},

			//Shift new children to the right
			shiftRight: function()
			{
				Deki.$(selectedChildren).addClass("selectedChild").addClass("childNode");

				//Animation complete
				Deki.nav.animComplete();

				//Compact node image padding
				Deki.nav.common.compactImagePad(selectedChildren);
			}
		},

		//-------------------------------Sibling--------------------------------

		sibling:
		{
			//Start animation
			startAnim: function()
			{
				if(selectedRGB) {
					Deki.$(selectedNode).find("a").css("backgroundColor", selectedRGB);
				}
				if(siblingRGB) {
					Deki.$(prevSelectedNode).find("a").css("backgroundColor", siblingRGB);
				}

				if(YAHOO.util.Dom.hasClass(prevSelectedNode, "parentOpen"))
				{
					//Hide children
					Deki.nav.sibling.hideSelectedChildren();
				}
				else
				{
					//Unhighlight selected
					Deki.nav.sibling.unhighlightSelected();
				}
			},

			//Hide previously selected node's children
			hideSelectedChildren: function()
			{
				Deki.nav.common.compactNodes(
					Deki.$("#" + navDivID + " div.selectedChild"),
					function()
					{
						Deki.$("#" + navDivID + " div.selectedChild").removeClass("selectedChild");
						Deki.nav.sibling.unhighlightSelected();
					}
				);
			},

			//Unhighlight previously selected node
			unhighlightSelected: function()
			{
				//Close parent node
				Deki.nav.common.closeParent(prevSelectedNode);

				//Unhiglight
				Deki.$(prevSelectedNode).removeClass("selected");

				//Highlight selected node
				Deki.nav.sibling.highlightSelected();
			},

			//Highlight selected node
			highlightSelected: function()
			{
				Deki.$(selectedNode).addClass("selected");

				//Open parent
				Deki.nav.common.openParent(selectedNode);

				//Show children
				if(selectedChildren)
				{
					Deki.nav.sibling.showChildren();
				}
				else
				{
					//Animation complete
					Deki.nav.animComplete();
				}
			},

			//Show children
			showChildren: function()
			{
				Deki.$(selectedChildren).addClass("selectedChild").addClass("childNode");

				//Open nodes
				Deki.nav.common.openNodes(
					selectedChildren,
					function()
					{
						//Animation complete
						Deki.nav.animComplete();
					}
				);

				//Shift right
				Deki.nav.common.shiftRight(selectedChildren);

				//Minimize image padding
				Deki.nav.common.compactImagePad(selectedChildren);
			}
		},

		//-------------------------------Hidden Nodes--------------------------------

		hiddenNodes:
		{
			//Start animation
			startAnim: function()
			{
			
				//Set content
				Deki.$(selectedNode).find("span").text(
					Deki.$(selectedNode).attr("content")
				  );

				//Set title
				Deki.$(selectedNode).find("a").attr("title",
					Deki.$(selectedNode).attr("contentTitle")
				);

				//Open hidden nodes
				Deki.nav.hiddenNodes.openNodes();
			},

			//Open hidden nodes
			openNodes: function()
			{
				//Get hidden nodes
				var hiddenNodes = Deki.nav.common.getNodesFromAttr(selectedNode, "hiddenNodes");

				Deki.$(hiddenNodes).show();

				//Animate hidden nodes open
				var anim = new YAHOO.util.Anim(
					hiddenNodes,
					{height: {to: properties.linkHeight}},
					animOpenCloseSpeed,
					YAHOO.util.Easing.easeIn
				);

				//Execute after animation has completed
				anim.onComplete.subscribe(
					function()
					{
						//Unmark node as having more nodes
						Deki.$(selectedNode).removeClass("moreNodes").removeAttr("hiddenNodes");

						//Unmark hidden nodes as being closed and hidden
						Deki.$(hiddenNodes).removeClass("closedNode").removeClass("hiddenNode");

						//Turn redirect off (previously started redirect will not be terminated)
						redirect = false;

						//
						selectedNode = prevSelectedNode;

						//Animation complete
						Deki.nav.animComplete();
					}
				);

				//Animate
				anim.animate();
			}
		}
	};
}();

//the onload event handler is available in /skins/common/javascript.php so we can flag it
