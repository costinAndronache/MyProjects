import proiectIPModul4.TextAnalyzer;
import com.aylien.textapi.TextAPIClient;
import com.aylien.textapi.TextAPIException;

public class Main {

    public static void main(String[] args) throws TextAPIException
    {

        System.out.println("Start!");
        TextAPIClient client = new TextAPIClient("ad4bcbb3", "4cd175be5b8b796e115420a1c145ae2a");
        String text1 = "The iPhone 5S (marketed with a stylized lowercase 's' " +
                "as iPhone 5s) is a smartphone developed by Apple Inc. It is " +
                "part of the iPhone line, and was released on September 20, " +
                "2013. Apple held an event to formally introduce the high-range " +
                "phone, and its mid-range counterpart, the iPhone 5C, on" +
                " September 10, 2013.";
        String title1 = "Apple";
        String text2 = "Barcelona forward Lionel Messi is not for sale and the club plan to discuss a new contract with the Argentine, says president Josep Maria Bartomeu.\n" +
                "\n" + "    Four-time Ballon d'Or winner Messi, 26, is reported to be a target for French side Paris St-Germain.\n" +
                "\n" + "    In an interview with radio station RAC1, posted on Barcelona's website,   Bartomeu said: \"The club will sit down and negotiate a new contract.\n" +
                "\n" + "    \"We will do what we have to, to ensure he's the best-paid player.\"\n" +
                "\n" + "    Messi scored 60 goals in 50 appearances last season but has struggled to match that goalscoring form in 2013-14.\n" +
                "\n" + "    He has scored 18 goals so far but just eight of those have been in the league, although he has provided 36 assists in 20 appearances.\n" +
                "\n" + "    His last league goal came in September, before he was out for five weeks with a hamstring injury.\n" +
                "\n" + "    \"He can do everything,\" said Barca coach Gerardo Martino. \"If he succeeds in other facets of his game, it doesn't matter if he scores.\n" +
                "\n" + "    \"Nothing surprises me with him. He controls the game well, passes the ball well, he is a good finisher, he can press and recover the ball.\n" +
                "\n" + "    \"He sees passes that most people can only see whilst watching the game on TV or in the stands, not ones that you can normally see on the field.\"";
        String title2="Messi";


        TextAnalyzer conceptAnalyzer = new ConceptAnalyzer(client,text1);
        System.out.println("\n Concept analyzer \n");
        for(String rez : conceptAnalyzer.analyze())
        {
            System.out.println(rez);
        }

        TextAnalyzer entityAnalyzer = new EntityAnalyzer(client,text1);
        System.out.println("\n Entity analyzer \n");
        for(String rez : entityAnalyzer.analyze())
        {
            System.out.println(rez);
        }

        TextAnalyzer summAnalyser = new SummaryAnalyzer(client,text1,title1);
        System.out.println("\n Summary analyzer \n");
        for(String rez : summAnalyser.analyze())
        {
            System.out.println(rez);
        }

        TextAnalyzer languageAnalyzer = new LanguageAnalyzer(client,text1);
        System.out.println("\n Language analyzer \n");
        for(String rez : languageAnalyzer.analyze())
        {
            System.out.println(rez);
        }

        TextAnalyzer hashtagAnalyzer = new HashtagAnalyzer(client,text1);
        System.out.println("\n Hashtag analyzer \n");
        for(String rez : hashtagAnalyzer.analyze())
        {
            System.out.println(rez);
        }

        TextAnalyzer perspectiveAnalyzer = new PerspectiveAnalyzer(client,text1);
        System.out.println("\n Perspective Analyzer \n");
        for(String rez : perspectiveAnalyzer.analyze())
        {
            System.out.println(rez);
        }

        TextAnalyzer impressionAnalyzer = new ImpressionAnalyzer(client,text1);
        System.out.println("\n Impression Analyzer analyzer \n");
        for(String rez : impressionAnalyzer.analyze())
        {
            System.out.println(rez);
        }



    }
}


