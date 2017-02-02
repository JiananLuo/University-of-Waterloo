
/*
 * I'm not crazy about this, but it avoids duplication of code.  Alternative would be 
 * server-size includes, but then I'd have to muck with a bunch of file renaming...
 */

function nav(page) {

	document.write('<div id="nav"><nav>');
	document.write('<ul id="main-nav">');
 	document.write('<li id="main-nav-about"><a href="about.html">About</a></li> ');
 	document.write('<li id="main-nav-schedule"><a href="schedule.shtml" >Schedule</a></li>');
 	document.write('<li id="main-nav-assignments"><a href="assignments.html" >Assignments</a></li>');
 	document.write('<li id="main-nav-resources"><a href="resources.html" >Resources</a></li>');
 	document.write('<li id="main-nav-piazza"><a href="https://piazza.com/class/hjqo9jjz5rp5we" >Piazza <img src="img/icon_external_site.gif" alt="" height="9" style="vertical-align:middle; margin-bottom: 5px;" width="9"></a></li>');
	document.write('</ul>');
	document.write('</nav></div>');

	$("#main-nav-" + page).addClass("on");
}


function footer() {
	document.write('<div id="footer"><footer>');
	document.write('<p><a href="http://uwaterloo.ca/">University of Waterloo</a></p>');
	document.write('<p><a href="https://cs.uwaterloo.ca/">Cheriton School of Computer Science</a></p>');
	document.write('<p><a href="https://cs.uwaterloo.ca/~bwbecker/">Byron Weber Becker</a>');
 	document.write('</footer></div>');

}