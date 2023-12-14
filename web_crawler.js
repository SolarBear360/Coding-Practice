const wiki = new URL("https://zh.wikipedia.org/");
const news = new URL("https://news.google.com/");

function find_html_head(htmlstr){
    let headk = 6;
    let titlek = 7;
    let i=0;
    findhead = false;
    while(i<htmlstr.length-headk){
        if(htmlstr.slice(i,i+headk) == "<head>"){
            console.log("found head");
            findhead = true;
        }
        if(findhead && htmlstr.slice(i,i+titlek) == "<title>"){
            console.log("found title")
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

async function ship(){
    await fetch(wiki).then(
        (response) => {
            return response.text();
        }
    ).then(
        (text) => {
            let head = find_html_head(text);
            console.log(head);
        }
    )

}

ship();