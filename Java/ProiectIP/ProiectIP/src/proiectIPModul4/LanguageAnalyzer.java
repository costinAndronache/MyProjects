import proiectIPModul4.TextAnalyzer;
import com.aylien.textapi.TextAPIClient;
import com.aylien.textapi.TextAPIException;
import com.aylien.textapi.parameters.LanguageParams;
import com.aylien.textapi.responses.Language;

import java.util.ArrayList;

/**
 * Created by Ana on 5/11/2015.
 */
public class LanguageAnalyzer implements TextAnalyzer {

    TextAPIClient client;
    String text;

    public LanguageAnalyzer( TextAPIClient client , String text )
    {
        this.client=client;
        this.text=text;
    }

    @Override
    public ArrayList<String> analyze()
    {
        Language response = null;
        try {
            response = client.language(new LanguageParams(text, null));
        } catch (TextAPIException e) {
            e.printStackTrace();
        }

        ArrayList<String > results = new ArrayList<String >();
        results.add(response.getLanguage());
        return results;
    }
    public void setText(String text)
    {
        this.text=text;
    }
}
