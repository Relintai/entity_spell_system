
using Newtonsoft.Json;
using UnityEngine;
/// <summary>
/// Base SpellData class.
/// </summary>
[System.Serializable]
public class PlayerSpellData {
    [SerializeField]
	int spellId;

    public int SpellId { get { return spellId; } set { spellId = value; } }

    public PlayerSpellData() {}

    public PlayerSpellData(int spellId)
    {
        this.spellId = spellId;
    }

	public virtual void Update(PlayerSpellDataComponent psdc)
	{
	}

    public virtual void Serialize(JsonWriter w)
    {
        ToJSON(this, w);
    }

    public static void ToJSON(PlayerSpellData psdc, JsonWriter w)
    {
        w.WritePropertyName("PlayerSpellData");
        w.WriteStartObject();

        w.WritePropertyName("SpellId");
        w.WriteValue(psdc.spellId);

        w.WriteEndObject();
    }

    public static void FromJSON(PlayerSpellData psdc, JsonReader r)
    {
        while (r.Read())
        {
            if (r.TokenType == JsonToken.PropertyName)
            {
                switch ((string)r.Value)
                {
                    case "SpellId":
                        psdc.spellId = (int)r.ReadAsInt32();
                        break;
                }
            }
            else if (r.TokenType == JsonToken.EndObject)
            {
                break;
            }
        }
    }
}
