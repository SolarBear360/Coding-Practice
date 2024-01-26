const wiki = new URL("https://zh.wikipedia.org/");
const news = new URL("https://news.google.com/");
const search_word = "home?hl=zh-TW&gl=TW&ceid=TW:zh-Hant";

function find_html_head(htmlstr){
    let headk = 6;
    let titlek = 7;
    let i=0;
    findhead = false;
    while(i<htmlstr.length-headk){
        if(htmlstr.slice(i,i+headk) == "<head>"){
            findhead = true;
        }
        if(findhead && htmlstr.slice(i,i+titlek) == "<title>"){
            let titlestr;
            let p = i+titlek;
            for(p;p<i+1000;p++){
                if(htmlstr.slice(p,p+titlek+1) == "</title>"){
                    titlestr = htmlstr.slice(i+titlek,p);
                    return titlestr;
                }
            }
        }
        i++;
    }
    return "找不到網頁標題";
}

async function find_html_url(htmlstr,mainurl){
    let i = 0;
    const absolute_urlk = 9;
    const relative_url = 2;
    let find_url = 0;
    let check_way = 0;
    while(i<htmlstr.length){
        if(htmlstr.slice(i,i+absolute_urlk) == "\"https://"){
            find_url = i;
            check_way = 1;
        }else if(check_way == 1 && htmlstr[i] == "\""){
            let geturl = htmlstr.slice(find_url+1,i);
            try{
                await fetch_url_head(geturl);
            }
            catch(error){
                console.log(error.name);
            }
            find_url = 0;
            check_way = 0;
        }

        if(htmlstr.slice(i,i+relative_url) == "\"/"){
            find_url = i;
            check_way = 2;
        }else if(check_way == 2 && htmlstr[i] == "\""){
            let geturl = mainurl + htmlstr.slice(find_url+2,i);
            try{
                await fetch_url_head(geturl);
            }
            catch(error){
                console.log(error.name);
            }
            
            find_url = 0;
            check_way = 0;
        }

        if(htmlstr.slice(i,i+relative_url+1) == "\"./"){
            find_url = i;
            check_way = 3;
        }else if(check_way == 3 && htmlstr[i] == "\""){
            let geturl = mainurl + htmlstr.slice(find_url+2,i);
            try{
                await fetch_url_head(geturl);
            }
            catch(error){
                console.log(error.name);
            }
            
            find_url = 0;
            check_way = 0;
        }

        i++;
    }
}

async function fetch_url_head(url){
    await fetch(url).then(
        (response) => {
            return response.text();
        }
    ).then(
        (text) => {
            let head = find_html_head(text);
            console.log("標題:"+head);
            console.log("連結:"+url);
        }
    )
}

fetch(news+search_word).then(
    (response) => {
        return response.text();
    }
).then(
    (text) => {
        find_html_url(text,news);
    }
)