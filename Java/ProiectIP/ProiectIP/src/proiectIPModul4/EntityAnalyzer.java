import proiectIPModul4.TextAnalyzer;
import com.aylien.textapi.TextAPIClient;
import com.aylien.textapi.TextAPIException;
import com.aylien.textapi.parameters.ConceptsParams;
import com.aylien.textapi.parameters.EntitiesParams;
import com.aylien.textapi.responses.*;

import java.util.ArrayList;

/**
 * Created by Ana on 5/11/2015.
 */
public class EntityAnalyzer implements TextAnalyzer
{
    TextAPIClient client;
    String text;
    EntitiesParams.Builder builder ;
    public EntityAnalyzer(TextAPIClient client , String text)
    {
        this.client=client;
        this.text=text;
        builder =  EntitiesParams.newBuilder();
    }

    public ArrayList<String> analyze()
    {
        builder.setText(this.text);
        ArrayList<String > results = new ArrayList<String >();

        Entities entities = null;
        try {
            entities = client.entities(builder.build());
        } catch (TextAPIException e) {
            e.printStackTrace();
        }

        for ( Entity e: entities.getEntities()) {
            for (String sf: e.getSurfaceForms())
            {
                System.out.println(sf);
                results.add(sf);
            }

        }
        return results;
    }
    public void setText(String text)
    {
        this.text=text;
    }
}
