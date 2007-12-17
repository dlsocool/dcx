<?php
function get_intro_dcxml() {
?>
<a name="top" id="top"></a>
<ol>
  <li class="sectionTitle"><a href="#Introduction">Introduction</a></li>
  <li class="sectionTitle"><a href="#GettingStarted">Getting started</a></li>
  <li class="sectionTitle"><a href="#XML">Some things you should know about XML</a></li>
  <li class="sectionTitle"><a href="#Rules">DCXML markup rules</a></li>
  <li class="sectionTitle"><a href="#Layout">Insert and layout dcx controls.</a></li>
  <li class="sectionTitle"><a href="#Pane">The power of pane </a></li>
  <li class="sectionTitle"><a href="#Styles">Cascading Control Styles</a> </li>
  <li class="sectionTitle"><a href="#Icons">Cascading Icon Definitions</a> </li>
  <li class="sectionTitle"><a href="#Templating">Templating</a></li>
  <li class="sectionTitle"><a href="#ElementRefference">Elements Refference</a> </li>
  <li class="sectionTitle"><a href="#AttributeRefference">Attributes Refference</a></li>
</ol>
<p> <span class="sectionTitle">Introduction 
  </span><a name="Introduction" id="Introduction"></a><a href="#top">go to top</a><br />
  <br />
DCXML is a way to make the creation and managing of dialogs more easy. Everything in DCX has to do with hierarchy: </p>
<ul>
  <li><strong>Child controls of container controls: </strong><br />
    Having to manage and keep track of what control is a child control is quite a task even for the most seasoned DCX user, however it's a totally essential skill to master if you want to take full advantage of DCX's awesome possibilities.</li>
  <li> <strong>Cell layout algorithm: </strong><br />
    On top of keeping track of all those ID's flying around if you really want to create full fletched dialogs that take advantage of CLA you'll have to keep track of an hierarchy that's not physical at all. For instance you can create virtual panes to display 1 or more controls. These visual panes only exist within the CLA's hierarchy.      </li>
</ul>
		<p>Confused yet? Don't worry a lot of people are, that's probably why CLA and DCX in general right now only has a select group of people that truly understand how to fully take advantage of how to create proper DCX dialogs. 
        This is where DCXML steps in. DCXML is a term for a way to describe how dialogs should look and act in XML. For those of you familiar with HTML it's almost the same principle. DCXML can be best viewed as a wrapper for all those /xdialog and /xdid calls you otherwise had to do in the on dialog init event. DCXML handles creation of controls and where/how they are positioned by automatically applying CLA.<br />
        <br />
        <strong>In short:</strong> DCXML seperates design from code. Code in mIRC, design in DCXML.</p>

        <p><span class="sectionTitle">Getting Started
        </span><a name="GettingStarted" id="GettingStarted"></a><a href="#top">go to top</a><br />
        <br />
DCXML should only be used with DCX 1.4 and higher, DCXML is defined in a seperate file and not within your script. You load DCXML by calling the dcxml file in the on init event of the dialog.
        <p>example:
        <pre>
dialog mydialog {
  size 200 200 200 200
}
on *:dialog:mydialog:init:*:{
  dcx Mark $dname events
  ;dcxml -d [DNAME] [Name of dialog element you wish to load] [path to dcxml file]
  dcxml -d $dname mydialog $qt($scriptdirdc.xml)
}
alias events {
     ;mydialog event handling goes here
}
alias dcxt dialog -m mydialog mydialog
</pre>


Although it might be easier to use the following if your familiar with dialog tables:
<pre>
alias dcxml.spawn dialog -m dcx. $+ $1 dcx
dialog dcx {
  size 0 0 0 0
}
on *:dialog:dcx.*:init:*:{
  tokenize 46 $dname
  dcx Mark $dname $2 $+ .events
  dcxml -d $dname $2 $qt($scriptdirdc.xml)
}
alias mydialog.events {
  ;mydialog event handling goes here
}
alias myotherdialog.events {
  ;mydialog event handling goes here
}
</pre>
/dcxml.spawn [dialog name as defined in the dcxml file]<br />
You can specify width height and caption of the dialog instance in DCXML so you only really need 1 dialog declaration in your mIRC script.
</p><br /><br />


<span class="sectionTitle">Some things you should know about XML </span><a name="XML" id="XML"></a><a href="#top">go to top</a><br />
	      <br />
        XML is built up using what is call Nodes, there are several Nodes but these are the ones you should know about because I will address them in this documentation. 
        <ul>
		  <li>	        <strong>Document Node </strong>: 
          In XML there is one single element that has all the other elements in it. The highest in the hierarchy as it were. Much like in HTML where &lt;html&gt; contains the entire page including &lt;head&gt; and &lt;body&gt; </li>
          <li>            <strong>Element Node </strong><br />
            Think of an element Node as a way to describe something. For instance: &lt;element&gt;&lt;/element&gt; <strong></strong>is a way to define an element, this element can have other elements inside of it like so <br />
&lt;element1&gt; &lt;element2&gt; &lt;/element2&gt; &lt;/element1&gt; You can also define an element that has nothing inside of it like so: <br />
&lt;element /&gt;</li>
          <li>            <strong>Attribute Node </strong><br />
            An attribute is a property you can set on an element like so: <br />
&lt;element attribute=�value�&gt;&lt;/element&gt; or <br />
&lt;element attribute=�value� /&gt; </li>
          <li>    <strong>Text Node </strong><br />
    Text Node is text inside an element: <br />
&lt;element attribute=�value�&gt; <br />
This text is considered a Text Node <br />
&lt;/element&gt; </li>
          <li>    <strong>Comment Node </strong> A Comment Node is an element that is not part of the hierarchy and is only there to place a comment of some sort. &lt;!--- This is a comment --&gt; 
        </ul>So an XML file always looks like this or any variation thereof: <br />
	<pre>
&lt;documentNode&gt;
	&lt;element1 attribute=�value1�&gt; 
		&lt;element2 /&gt;
	&lt;/element1&gt; 
	&lt;element1 attribute=�value2�&gt;
		&lt;element2 /&gt; 
	&lt;/element1&gt; 
&lt;/documentNode&gt; &nbsp; 
</pre>

        <span class="sectionTitle">DCXML markup rules</span> <a name="Rules" id="Rules"></a><a href="#top">go to top</a><br />
        <br />
        The beauty of XML lies in the fact that you can freely name all your elements and attributes to suit your situation. However as the name DCXML implies it differs from XML a bit. The only difference is that we've already defined all the Elements and Attributes that the parser understands. Much like XHTML has defined &lt;h1&gt; to be a header and &lt;hr&gt; to be a horizontal ruler DCXML has defined &lt;control&gt; to be a control for instance. 
            <br />
            <br />
            <strong>A DCXML file always starts with this: 
            </strong><br />
<pre>
&lt;dialogs&gt; 
	�
&lt;/dialogs&gt; 
</pre>
Which will make more sense later, a DCXML file describes one or more dialogs. It (hopefully) won't be a surprise the next step is as followed:
<pre>
&lt;dialogs&gt; 
	&lt;dialog&gt; 
		�� 
	&lt;/dialog&gt; 
&lt;/dialogs&gt; 
</pre>
As you can see we are defining 1 dialog in this DCXML file now, you'll HAVE to give dialog elements a name attribute to distinguish between them the reason why becomes apparent when you define multiple dialogs. <strong>note:</strong> this value of name doesn't have to equal $dname. 
<pre>
&lt;dialogs&gt; 
	&lt;dialog name=�mydialog�&gt; 
		�� 
	&lt;/dialog&gt; 
	&lt;dialog name=�myotherdialog�&gt;
		�� 
	&lt;/dialog&gt; 
&lt;/dialogs&gt; 
</pre>
        This is the basic setup of a DCXML file which is pretty straightforward. Now it's up to you to define your dialogs within the dialog elements! How? Keep on reading! 
		
        <br />
        <span class="sectionTitle"><br />
        Insert and layout dcx controls <a name="Layout" id="Layout"></a></span><a href="#top">go to top</a><br />
        <br />
Forget what you know about creating dialogs! No more painstaikingly aligning controls to just the right x or h, no more calculating 
control sizes for resizeable dialogs, no more keeping track of ID's, never again trace your xdialog and xdid's to what they're exactly doing! DCXML handles all of this.
<br />
ok so lets take it a step at a time shall we?
<br />
<br />
<strong>No more ID's?</strong><br />
Thats right, only id those controls you are going to work with the rest will be assigned an id (2000+number of parsed controls so avoid control id's >= 2000)
<pre>
&lt;control type=&quot;panel&quot;&gt;
	&lt;control type=&quot;text&quot;&gt;
&lt;/control&gt;
</pre>
This will create a text control on a panel without having to remember the id of the pane to insert the text inside it. There is no limitation
to how deep you can nest controls. This makes creating complex control structures a breeze. 
<pre>
&lt;control type=&quot;panel&quot;&gt;
	&lt;control type=&quot;check&quot; id=&quot;2&quot;&gt;
	&lt;control type=&quot;text&quot;&gt;
&lt;control /&gt;
</pre>
ID only those controls you are planning to script with in mIRC.<br />
<strong>No more XYWH!</strong><br />
DCXML will place and size controls for you, you just tell DCXML that something should be smaller or bigger.
<pre>
&lt;dialog name=&quot;somedialog&quot;&gt;
	&lt;control type=&quot;panel&quot; cascade=&quot;h&quot;&gt;
		&lt;control type=&quot;check&quot; id=&quot;2&quot; /&gt;
		&lt;control type=&quot;text&quot;/&gt;
	&lt;/control&gt;
&lt;/dialog&gt;
</pre>
In this example the panel will take all the available space on the dialog because its the only child of the dialog. Inside 
the panel the check and text will take 50% of the space inside the panel because  100% space devided by 2 controls that want to take
it is 50%. The controls will appear next to eachother due to the cascade attribute on the panel ( see cascade attribute ).<br />

All very handy but what if you want the text to take only 25% of the available space ? Is that possible ? Yes it is !
<pre>
&lt;dialog name=&quot;somedialog&quot;&gt;
	&lt;control type=&quot;panel&quot; cascade=&quot;h&quot;&gt;
		&lt;control type=&quot;check&quot; id=&quot;2&quot; weight=&quot;3&quot;/&gt;
		&lt;control type=&quot;text&quot; weight=&quot;1&quot;/&gt;
	&lt;/control&gt;
&lt;/dialog&gt;
</pre>

<p>As you noticed we've added an attribute called weight this hints the parser how to size the controls inside the pane.</p>
<p>The space inside the panel is 100% we already know this, of this space the check wants to take 3 parts and the text
 wants to take 1 part. So to give them both what they
 want  3+1 has to equal 100%. So 4 equals 100% and the check takes 3/4th so 75% and the text takes 1/4th or 25%.<br />
 
 
To check if you understood weights have a look at this DCXML and think for yourself how much space the check and text take inside 
the panel
<pre>
&lt;dialog name=&quot;somedialog&quot;&gt;
	&lt;control type=&quot;panel&quot; weight=&quot;3&quot;&gt;
		&lt;control type=&quot;check&quot; id=&quot;2&quot; cascade=&quot;h&quot; weight=&quot;10&quot;/&gt;
		&lt;control type=&quot;text&quot; weight=&quot;5&quot;/&gt;
	&lt;/control&gt;
&lt;/dialog&gt;
</pre>

If you thought that the check takes 2/3rd (10/15th) and the text 1/3rd (5/15th) you know your stuff! Finally lets take a look another 
case:
<pre>
&lt;dialog name=&quot;somedialog&quot;&gt;
	&lt;control type=&quot;panel&quot; cascade=&quot;h&quot; weigth=&quot;9&quot;&gt;
		&lt;control type=&quot;check&quot; id=&quot;2&quot; weight=&quot;10&quot;/&gt;
		&lt;control type=&quot;text&quot; weight=&quot;5&quot;/&gt;
	&lt;/control&gt;
	&lt;control type=&quot;panel&quot; cascade=&quot;h&quot; weigth=&quot;10&quot;&gt;
		&lt;control type=&quot;check&quot; id=&quot;2&quot; weight=&quot;10&quot;/&gt;
		&lt;control type=&quot;text&quot; weight=&quot;5&quot;/&gt;
	&lt;/control&gt;
&lt;/dialog&gt;
</pre>
Here there's 2 panels on the dialog, they will not be placed next to eachother but they will be stacked vertically. This because there
is no cascade attribute set on the dialog element and stacking vertically is the default behaviour. The top panel 
will take 9/19th of the space on the dialog and the bottom one 10/19th.<br />
<br />
Ok so hopefully by now you grasp how you can manipulate the layout by modifying the weight and cascade attributes. But what if you dont want a control to size
vertically, horizontally or both ? and what if you want to specify a width/height in pixels ?<br />


All  you have to do is either specify the height and/or width:
<pre>
&lt;dialog name=&quot;somedialog&quot;&gt;
	&lt;control type=&quot;panel&quot; cascade=&quot;h&quot; height=&quot;120&quot;&gt;
		&lt;control type=&quot;check&quot; id=&quot;2&quot; width=&quot;20&quot;/&gt;
		&lt;control type=&quot;text&quot; /&gt;
	&lt;/control&gt;
	&lt;control type=&quot;panel&quot; cascade=&quot;h&quot; weigth=&quot;1&quot;&gt;
		&lt;control type=&quot;check&quot; id=&quot;2&quot; heigth=&quot;20&quot; width=&quot;20&quot;/&gt;
		&lt;control type=&quot;text&quot; weight=&quot;5&quot;/&gt;
	&lt;/control&gt;
&lt;/dialog&gt;
</pre>

<p>In this example the top panel is 120px in height, this control will not size vertically when resized but WILL resize horizontally. The 2nd panel will take the remaining space.
  The check inside the first panel is 20px wide and will not resize in width but will in height. The check inside the 2nd panel is 20px wide and 20px high and will never resize.
    <br />
    <span class="sectionTitle"><br />
The power of pane </span><a name="Pane" id="Pane"></a><a href="#top">go to top</a><br />
<br />
A very powerful element to help you layout your dialog the way you want is the &lt;pane&gt; <br />
A pane can be best viewed as a panel control without actually creating a control on the dialog.
<pre>
&lt;dialog name=&quot;somedialog&quot;&gt;
	&lt;pane cascade=&quot;h&quot; weight=&quot;3&quot;&gt;
		&lt;control type=&quot;check&quot; id=&quot;2&quot; width=&quot;20&quot;/&gt;
		&lt;control type=&quot;text&quot; /&gt;
	&lt;/pane&gt;
	&lt;pane cascade=&quot;h&quot; weight=&quot;1&quot;&gt;
		&lt;control type=&quot;check&quot; id=&quot;2&quot; heigth=&quot;20&quot; width=&quot;20&quot;/&gt;
		&lt;control type=&quot;text&quot; weight=&quot;5&quot;/&gt;
	&lt;/pane&gt;
&lt;/dialog&gt;
</pre>
<p>This is the same as using a panel control in the above section but no control is actually created a &lt;pane&gt; virtually groups controls so is performence wise best to use. Of course &lt;pane&gt; doesn't replace a panel control as you can't style a pane.<br />
<strong>Note:</strong> a &lt;pane&gt; cannot have a fixed width or heigth!</p>
<p> <br />


  <span class="sectionTitle">Cascading Control Styles </span>
    <a name="Styles" id="Styles"></a><a href="#top">go to top</a><br />
    <br />
    One of the major benefits of using DCXML is that you can define a multiple controls styles in one easy definition. You can style per ID, Class &amp; Type. On top of that you can set global and local style definitions. <br />
    Style definitions are grouped in the &lt;styles&gt; element. This &lt;styles&gt; element can be a child of &lt;dialogs&gt; which will effect ALL dialogs or &lt;dialog&gt; to only style a certain dialog. You can also style directly on the &lt;control&gt;.
</p>
  </p>
  </p>
</p>
<pre>
&lt;dialogs&gt; 
	&lt;styles&gt; 
		&lt;style type=�text� fontname=�Trebuchet MS�/&gt;
	&lt;/styles&gt; 
	&lt;dialog&gt;
		&lt;styles&gt; 
			&lt;style type=�text� fontname=�Tahoma� /&gt; 
		&lt;/styles&gt;
		&lt;control type=�text� fontname=�Verdana�&gt; 
        	This text is in Verdana 
		&lt;/control&gt;
		 � </pre>
        In the above example the text control will appear in Verdana because the most explicit style will always be applied. <br />
If we remove the fontname attribute on the control the text will be in Tahoma because that's more explicit then the definition in the global styles definition. 
<pre>
&lt;dialogs&gt;
	&lt;styles&gt;
		&lt;style type=�text� fontname=�Trebuchet MS� /&gt;
		&lt;style class=�TahomaText� fontname=�Tahoma� /&gt; 
		&lt;style id=�10� fontname=�Verdana� /&gt; 
	&lt;/styles&gt;
	&lt;dialog&gt;
		&lt;control class=�TahomaText� type=�text� id=�10�&gt; 
        	This text is in Verdana 
	&lt;/control&gt; 
    ...
</pre>
        In the above example the text will be in Verdana because id is more explicit then class and text. 
        The exact order of precedence is: id, class, type. If DCXML can't match id it will try to match class and then match on type. 
&nbsp; 
        In addition to &lt;style&gt; there's also an &lt;all&gt; element which is the exact same but will apply to <strong>every </strong> control on the dialog(s). <strong>Note: </strong> This element has the lowest precedence and will only be applied if DCXML cant match on id, class or text.<br />
        <br />
        <span class="sectionTitle"> Cascading Icon Definitions </span><a name="Icons" id="Icons"></a><a href="#top">go to top</a><br />
        <br />
Icon libraries for controls are applied in a similar way as style definitions. 
<pre>
&lt;dialogs&gt;
	&lt;icons&gt;
		&lt;icon type=&quot;treeview&quot; indexmax=&quot;40&quot; src=&quot;$_scriptdir $+ controls.icl&quot; /&gt; 
		&lt;icon class=&quot;Pastel&quot; indexmax=&quot;40&quot; src=&quot;$_scriptdir $+ pastel.icl&quot; /&gt; 
		&lt;icon id=&quot;10&quot; index=&quot;20&quot; src=&quot;$_scriptdir $+ pastel.icl&quot; /&gt; 
		&lt;icon type=&quot;listview&quot; indexmax=&quot;40&quot; src=&quot;$_scriptdir $+ controls.icl&quot; /&gt; 
	&lt;/icons&gt; 
    .. 
</pre>
        <p>Like styles icons can appear as child of &lt;dialogs&gt; and &lt;dialog&gt;.<br />
          DCXML will first try to match in the &lt;dialog&gt; icons definition. When unsuccessful it will parse the &lt;dialogs&gt; icons definition. 
            Use the index attribute if you want to load up a single icon, for multiple icons you can use indexmin and indexmax. DCXML will loop from indexmin and indexmax and load up those icons. Indexmin and indexmax default to zero and min <strong>has </strong> to be smaller then max. <br />
            <br />
            <span class="sectionTitle">Templating
            </span><a name="Templating" id="Templating"></a><a href="#top">go to top</a><br />
            <br />
		  DCXML allows you to template dialog elements you use really often like alot of your dialogs will have a header of some sort, to prevent you from defining the header 
		  everytime you create a new dialog you can template it.
<pre>&lt;dcxml&gt;<br />	&lt;dialogs&gt;<br />		&lt;templates&gt;<br />			&lt;template name=&quot;header&quot;&gt;<br />				&lt;control type=&quot;panel&quot; cascade=&quot;h&quot; height=&quot;70&quot;&gt;<br />					&lt;control width=&quot;253&quot; height=&quot;70&quot; type=&quot;image&quot; eval=&quot;1&quot; src=&quot;$+($_scriptdir,dcx.jpg)&quot; /&gt;<br />					&lt;control width=&quot;547&quot; height=&quot;70&quot; type=&quot;image&quot; eval=&quot;1&quot; src=&quot;$+($_scriptdir,top_bg.jpg)&quot; /&gt;<br />					&lt;control type=&quot;panel&quot; bgcolour=&quot;16318463&quot; /&gt;<br />				&lt;/control&gt;<br />			&lt;/template&gt;<br />		&lt;/templates&gt;
		&lt;dialog name=&quot;somedialog&quot;&gt;<br />			&lt;calltemplate name=&quot;header&quot; /&gt;<br />			&lt;control type=&quot;panel&quot;&gt;
			...<br />	</pre>
			&lt;template&gt; can only be defined in the &lt;templates&gt; section of &lt;dialogs&gt;. You call a template using the &lt;calltemplate&gt; element.
			calltemplate can not have any children but can be called as many times as you like.<br />
			<br />
	Here's another use for templates
<pre>&lt;template name=&quot;OkCancel&quot;&gt;<br />		&lt;control type=&quot;panel&quot; styles=&quot;vgradient&quot; cascade=&quot;h&quot; margin=&quot;0 5 0 5&quot; height=&quot;35&quot;&gt;<br />			&lt;pane cascade=&quot;v&quot; weight=&quot;1&quot; /&gt;<br />			&lt;control type=&quot;button&quot; styles=&quot;vgradient&quot; eval=&quot;1&quot; id=&quot;1&quot; bgcolour=&quot;$rgb(255,255,255)&quot; 
				caption=&quot;Cancel&quot; width=&quot;100&quot; height=&quot;25&quot; /&gt;
			&lt;control type=&quot;button&quot; caption=&quot;Ok&quot; id=&quot;2&quot; width=&quot;100&quot; height=&quot;25&quot; /&gt;
		&lt;/control&gt;<br />	&lt;/template&gt;
</pre>
	<p>This will define Ok and Cancel button's that are always right alligned on the dialog and will resize properly. The Cancel button has id  1 and OK button 2. Now 
	all you need to do to add this to a dialog is 
&lt;calltemplate name=&quot;OkCancel&quot; /&gt; </p>
	<p>            <span class="sectionTitle">Element </span><span class="sectionTitle">Refference</span><a name="ElementRefference" id="ElementRefference"></a>
	<a href="#top">go to top</a>	  <br />
            <br />
      There are only a few different Elements in DCXML, this is to hopefully keep the markup simple.<br />
      Another big reason a treeview for instance is created like this:<br />
&lt;control type=&quot;treeview&quot; /&gt;<br />
instead of <br />
&lt;treeview /&gt; <br />
is because this way dcx can grow without having to add new dcxml elements each time a new control is made.<br />
An element can not just exist anywhere you like, here's a complete list of elements and where they may be placed:
if they have dialog listed as parent node but not icons that means that you can't specify the element inside an icons element. <br />
If you do so it will be ignored<br />
</ul>
</p>
        <table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;dialogs&gt; </span><br />
        dialogs is the document node this means it has to be at the top of the hierarchy see �DCXML markup rules� for more information. </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top">&lt;dialog&gt;, &lt;icons&gt; and &lt;styles&gt; </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top"><em>none </em></td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;dialog&gt; </span><br />
        The dialog element is where you can define your dialog in. </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top">&lt;control&gt;, &lt;pane&gt;, &lt;icons&gt; and &lt;styles&gt; </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top"><em>none </em></td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;control&gt; </span><br />
        The control element creates as you might expect a control on your dialog, you can specify which by setting the type attribute: &lt;control type=�listview� /&gt; creates a listview etc. </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top">&lt;control&gt; (If the parent control element is a Container type) <br />
&lt;pane&gt; (if control is of type Panel or Box) 
        &lt;item&gt; (Control specific allows you to add items to toolbars, lists, treeview's etc) </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top">&lt;control&gt;, &lt;pane&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;item&gt; </span><br />
        Control specific allows you to add items to toolbars, lists, treeview's etc </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top">&lt;item&gt; </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top">&lt;control&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;pane&gt; </span><br />
        Pane is a way to group controls and manage their display in a grouped manner. </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top">&lt;control&gt;, &lt;pane&gt;, </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top">&lt;control&gt; (if control has CLA such as PANE and BOX controls), &lt;pane&gt; </td>
  </tr>
</table>
� 
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;styles&gt; </span><br />
        styles is an element that groups style elements. </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top">&lt;style&gt; </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top">&lt;dialogs&gt;(global), &lt;dialog&gt;(local) </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;style&gt; </span><br />
        style allows you to style a control/class or id. </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top"><em>none </em></td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top">&lt;styles&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;all&gt; </span><br />
        Handy element to style EVERYTHING on your dialog. </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top"><em>none </em></td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top">&lt;styles&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;icons&gt; </span><br />
        icons groups icon elements </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top">&lt;icon&gt; </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top">&lt;dialogs&gt;(global), &lt;dialog&gt;(local) </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;icon&gt; </span><br />
        icon allows you to specify a control/class or id's image list </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top"><em>none </em></td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top">&lt;icons&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;templates&gt; </span><br />
    Container for templates </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top">&lt;template&gt;</td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top">&lt;dialogs&gt;</td>
  </tr>
</table>
<br />
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;template&gt; </span><br />
    icon allows you to specify a control/class or id's image list </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top">Any valid child of &lt;dialog&gt; except for &lt;calltemplate&gt; </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top">&lt;templates&gt;</td>
  </tr>
</table>
<br />
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="638" colspan="2" valign="top"><span class="subSectionTitle">&lt;calltemplate&gt; </span><br />
    Applies a certain template </td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Child nodes: </strong></td>
    <td width="529" valign="top">None</td>
  </tr>
  <tr>
    <td width="109" valign="top"><strong>Parent Nodes: </strong></td>
    <td width="529" valign="top">Any valid &lt;dialog&gt; child element except for &lt;calltemplate&gt;</td>
  </tr>
</table>
<p><span class="sectionTitle">Attribute Refference<a name="AttributeRefference" id="AttributeRefference"></a></span>
<a href="#top">go to top</a></p>
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">eval</td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top"><strong>every element</strong></td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Specifies wheter to evaluate identifiers in the attributes and textNode of the element. Please note when set the DCXML parser will send the command to mIRC and then recieve it back in DCX this is slightly slower then normal because when this attribute is not set the DCXML parser calls the appropiate function internally. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">not applicable.</td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">as soon as this attribute is set it will evaluate identifiers. so <span class="subSectionTitle">eval=&quot;&quot;</span> is enough to make it evaluate. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�text� eval=&quot;1&quot; caption=�$me� /&gt; </td>
  </tr>
</table>
<br />
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">w <span class="style1">&amp;</span> h </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;dialog&gt;</td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the width or height of the dialog </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">not applicable.</td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">&nbsp;</td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;dialog w=�200� h=&quot;400&quot; &gt; </td>
  </tr>
</table>
<br />
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">center</td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;dialog&gt;</td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Centers the dialog when created.</td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">not applicable.</td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">any</td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;dialog w=�200� h=&quot;400&quot; center=&quot;&quot;&gt; </td>
  </tr>
</table>
<br />
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">type </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Tells the DCXML parser what kind of control you want to create. Name as supplied to /xdialog �c or /xdid �c </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">Panel </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">pbar , treeview, toolbar, statusbar , listview, trackbar, rebar, colorcombo ,button, richedit, ipaddress, updown ,webctrl, line, box, radio, check, edit ,scroll, image, list link, text, divider, panel ,tab, window, dialog </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�listview� /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">weight </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt; &lt;pane&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Give's a control or pane a weight value so that the CLA can determine it's size against it's siblings. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">0 </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any numerical value greater then zero. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�listview� weight=�4� /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">height </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt; &lt;pane&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Give's a control or pane a fixed height in pixels. The control will not size vertically when this attribute is set on an element </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">0 </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any numerical value greater then zero to indicate height in pixels </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�listview� /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">width </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt; &lt;pane&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Give's a control or pane a fixed width in pixels. The control will not size horizontally when this attribute is set on an element </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">0 </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any numerical value greater then zero to indicate width in pixels </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�listview� /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">margin </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;pane&gt;&lt;dialog&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Give's a dialog or pane a margin. All the childs will be placed at the offset specifed </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">0 0 0 0 </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">LEFT TOP RIGHT BOTTOM as integers. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;pane margin=�20 20 20 20� /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">styles </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the control styles </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any valid style on the control </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�listview� styles=�report grid subitemimage fullrow� /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">caption </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt; &lt;dialog&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">If control allows text to be added this will set the text. For &lt;dialog&gt; this sets the dialog title. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any valid XML character for instance using �&amp;� can result in text to be cut off. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�text� caption=�This is a text control!� /&gt; <br />
        or <br />
&lt;control type=�text�&gt;This is a text control!&lt;/control&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Notes: </strong></td>
    <td width="523" valign="top"><ul>
      <li>You don't have to use the caption attribute if you set the Text Node on the element (see above) it will do the exact same.</li>
      <li>When you use the Text Node method there's no limit on how much text you want to input.</li>
      <li>For some controls \c and \b are shortcuts to mIRC's colour and bold code respectively. </li>
      <li>mIRC identifiers <strong>WILL </strong> be evaluated if the eval attribute is set on the element. </li>
    </ul></td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">tooltip </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the control's tooltip </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any valid tooltip control </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�text� tooltip=�some description� /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">cascade </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;pane&gt;&lt;dialog&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the direction in which the child &lt;panes&gt;&lt;controls&gt; are placed. Specify �h� and all the children will appear next to each other. �v� makes them appear underneath each other. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">v </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">h v </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�text� tooltip=�some description� /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">textcolour </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;style&gt;&lt;item&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets text colour </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Numeric greater then zero. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;item caption=�redtext� textcolour=�255� /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">textbgcolour </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;style&gt;&lt;item&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets text background colour </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Numeric greater then zero. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;item caption=�redbgtext� textcolour=�255� /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">bgcolour </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;style&gt;&lt;item&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets background colour </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Numeric greater then zero. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;item caption=�redbgt� bgcolour=�255� /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">icon </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;item&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the icon index to be used by the control or item. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Numeric greater then or equal to zero. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;item icon=�0� /&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>&nbsp; </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top" class="subSectionTitle">iconsize </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;style&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the icon size. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Numeric greater then or equal to zero. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;item icon=�0� /&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>&nbsp; </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top" class="subSectionTitle">integral </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control type=�treeview�&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets icon spacing in the treeview </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Numeric greater then zero. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�treeview� integral=�1�&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">fontstyle </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;style&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the fontstyle </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any valid fontstyle switch </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�text� fontstyle=�b�&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">charset </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;style&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the character set of the font </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any valid character set </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�text� charset=�ansii�&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">fontsize</td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;style&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the font size </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any font size </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�text� fontsize=�16�&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">fontname </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;style&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the font </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any font </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�text� font=�Trebuchet MS�&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">border </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;dialog&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the border on a control dialog </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any valid border switch </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;dialog name=&quot;mydialog&quot; border=&quot;btmnzy&quot;&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">cursor </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;style&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the default cursor for a control </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any valid cursor name </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�text� cursor=�wait�&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">indent </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;item&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Sets the indentation of comboex items. In future this will support more controls and integral will be synonymous with this attribute. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">0 or greater </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;item indent=�5� &gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">flags </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;item&gt;&lt;icon&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Allows you to pass flags when creating controls, items, icons. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any valid flag </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;item caption=&quot;these&quot; icon=&quot;20&quot; flags=&quot;v&quot; /&gt; <br />
        creates a toolbar button with a dropdown arrow if this item is child of a toolbar. </td>
  </tr>
</table>
<br />

<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">src </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt;&lt;item&gt;&lt;icon&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Pointer to files, for instance icon resources,a bitmap, or an URL for link controls. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">Any valid pathname </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;icon type=&quot;treeview&quot; indexmax=&quot;40&quot; src=&quot;$_scriptdir $+ controls.icl&quot; /&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">cells </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control type=�statusbar�&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Special attribute to tell DCX how many cells there are and how big they're going to be </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">N [N N N �.] </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�statusbar� cells=&quot;100 200 300 400 -1&quot;&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">minheight </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Special attribute to tell direct child controls of the rebar the minimal height the bar of the rebar band. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">0 or greater. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�panel� minheight=&quot;100&quot;&gt; </td>
  </tr>
</table>
� 
<table cellspacing="0" cellpadding="0">
  <tr>
    <td width="115" valign="top" class="subSectionTitle">minwidth </td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Applies to: </strong></td>
    <td width="523" valign="top">&lt;control&gt; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Description: </strong></td>
    <td width="523" valign="top">Special attribute to tell direct child controls of the rebar the minimal width the bar of the rebar band. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Default value: </strong></td>
    <td width="523" valign="top">&nbsp; </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Valid values: </strong></td>
    <td width="523" valign="top">0 or greater. </td>
  </tr>
  <tr>
    <td width="115" valign="top"><strong>Example: </strong></td>
    <td width="523" valign="top">&lt;control type=�panel� minwidth=&quot;100&quot;&gt; </td>
  </tr>
</table>
<?php
} ?>
