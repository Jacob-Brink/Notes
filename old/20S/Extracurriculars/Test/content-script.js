var playlist_locator = ".style-scope.ytd-app#content .style-scope.ytd-app#page-manager .style-scope.ytd-page-manager.hide-skeleton .style-scope.ytd-watch-flexy#columns .style-scope.ytd-watch-flexy#secondary .style-scope.ytd-watch-flexy#secondary-inner .style-scope.ytd-watch-flexy#playlist .style-scope.ytd-playlist-panel-renderer#container .playlist-items.yt-scrollbar-dark.style-scope.ytd-playlist-panel-renderer#items";

alert("works");

function getElementSearcherByGeneology(array) {
    let querySelectionString="";
    array.forEach(sElem => {
	className=sElem['class'];
	elemID=sElem['id'];
	querySelectionString += " ";
	if (className != "") {
	    querySelectionString += `.${className.replace(/ /g,".")}`; 
	}
	if (elemID != "") {
	    querySelectionString += `#${elemID}`;
	}
    });
    return function() {
	document.querySelectorAll(querySelectionString);
    };
}



//checked
function getPlaylistArray(dom) {
    let children = dom.children;
    let arr = [];
    for (var i = 0; i < children.length; i++) {
	arr.push(children[i].querySelector("a").href);
    }
    console.log(arr);
    return arr;
}

//checked
function waitForElementToDisplay(selector, time, callback) {
    console.log("Trying agains");
    console.log(document.querySelectorAll(selector));
    if(document.querySelectorAll(selector).length!=0) {
	callback(document.querySelectorAll(selector)[0]);
	return;
    }
    else {
	setTimeout(function() {
	    waitForElementToDisplay(selector, time, callback);
	}, time);
    }
}
handleRequest("https://www.youtube.com/watch?v=Zhg070ItM3E");

waitForElementToDisplay(playlist_locator, 500, getPlaylistArray);


//headers used for every response
const init = {
    headers: {
	'content-type': 'application/json',
	'Access-Control-Allow-Origin': '*',
	'Access-Control-Allow-Methods': 'GET',
	'Access-Control-Allow-Headers': 'Content-Type'
    }
};

async function handleRequest(userURL) {
    var videoID = new URL(userURL).searchParams.get('id');
    if (!videoID) {
	return new Response(JSON.stringify({ error: 'Video id required' }), init, { status: 400 });
    }

    //construct youtube url to fetch
    var url = `https://www.youtube.com/watch?v=${videoID}`;

    var response = await fetch(url);
    var text = await response.text();

    //determine if the video is valid
    var isValid = text.split('ytplayer.config = ')[1];
    if (!isValid) {
	return new Response(JSON.stringify({ error: 'Invalid video id' }), init);
    }

    //TODO - better check if valid video id

    //strip down to just json
    var fullJSON = isValid.split(';ytplayer.load')[0];
    var obj = JSON.parse(fullJSON);

    var videoInfo = obj['args']['player_response'];
    var clean = videoInfo.replace('\u0026', '&');
    var data = JSON.parse(clean);

    console.log(data);

    // Returns all video info
    // const init = { headers: { 'content-type': 'application/json' } };
    // return new Response(JSON.stringify(data), init);

    //sort by highest resolution
    var formats = data.streamingData.formats.sort((a, b) => (a.width > b.width ? -1 : 1));

    //TODO - decode video url from cipher

    if (formats[0].url) {
	//build response
	var response = {
	    title: data.videoDetails.title,
	    video: formats[0].url,
	    thumbnail: data.videoDetails.thumbnail.thumbnails[0].url
	};
	return new Response(JSON.stringify(response), init);
    } else {
	return new Response(JSON.stringify({ error: 'Unable to determine URL due to youtube cipher' }), init);
    }
}

addEventListener('fetch', (event) => {
    return event.respondWith(handleRequest(event.request));
});

// var buttonHeader;

// function downloadPlaylistExtension() {
//     console.log("Playlist Extension is loaded");
//     var parentCLASS = "style-scope ytd-playlist-panel-renderer";
//     var childID = "top-level-buttons";

//     children = document.querySelectorAll(`.${parentCLASS} #${childID}`);
//     console.log(children);
//     ytd-menu-renderer.ytd-playlist-panel-renderer > div:nth-child(1)
//     //*[@id="top-level-buttons"]

//     buttonHeader = document.getElementById("top-level-buttons");
//     if (buttonHeader == null) {
// 	alert("Help");
//     }
//     document.getElementById("top-level-buttons").innerHTML += `<ytd-toggle-button-renderer class="style-scope ytd-menu-renderer style-grey-text size-default" use-keyboard-focused="" button-renderer="true" is-icon-button="" has-no-text="">
//     <a class="yt-simple-endpoint style-scope ytd-toggle-button-renderer" tabindex="-1">
//       <yt-icon-button id="button" class="style-scope ytd-toggle-button-renderer style-grey-text size-default">
// 	<!--css-build:shady-->
// 	<button id="button" class="style-scope yt-icon-button" aria-label="Loop playlist" aria-pressed="false">
// 	  <yt-icon class="style-scope ytd-toggle-button-renderer">
// 	    <svg viewBox="0 0 24 24" preserveAspectRatio="xMidYMid meet" focusable="false" class="style-scope yt-icon" style="pointer-events: none; background-color: red; display: block; width: 100%; height: 100%;">
// 	      <g class="style-scope yt-icon">
// 		<path d="M7 7h10v3l4-4-4-4v3H5v6h2V7zm10 10H7v-3l-4 4 4 4v-3h12v-6h-2v4z" class="style-scope yt-icon"></path>
// 	    </g></svg><!--css-build:shady-->


// 	  </yt-icon>
// 	</button>
//       </yt-icon-button>
//     </a>
//   </ytd-toggle-button-renderer>
// `;//*/

// }


// waitForElementToDisplay("#top-level-buttons", 500, downloadPlaylistExtension);

// var str="asdfaasdf<g><svg class='svg-icon' viewBox='0 0 20 20'><path d='M17.064,4.656l-2.05-2.035C14.936,2.544,14.831,2.5,14.721,2.5H3.854c-0.229,0-0.417,0.188-0.417,0.417v14.167c0,0.229,0.188,0.417,0.417,0.417h12.917c0.229,0,0.416-0.188,0.416-0.417V4.952C17.188,4.84,17.144,4.733,17.064,4.656M6.354,3.333h7.917V10H6.354V3.333z M16.354,16.667H4.271V3.333h1.25v7.083c0,0.229,0.188,0.417,0.417,0.417h8.75c0.229,0,0.416-0.188,0.416-0.417V3.886l1.25,1.239V16.667z M13.402,4.688v3.958c0,0.229-0.186,0.417-0.417,0.417c-0.229,0-0.417-0.188-0.417-0.417V4.688c0-0.229,0.188-0.417,0.417-0.417C13.217,4.271,13.402,4.458,13.402,4.688'></path></svg></g>";
// saveButton.insertAdjacentHTML('beforeend', str);

// saveButton.setAttribute('id', 'download_button');
// saveButton.onclick=function(){
//     alert("It works!");
//     return false;
// }

// var playlist_widget=document.getElementById("playlist-action-menu");

// if (playlist_widget == null) {
//     alert("NULL");
// } else {
//     alert("LOADED");
//     playlist_widget.appendChild(saveButton);
//     alert("Finished");
// }


