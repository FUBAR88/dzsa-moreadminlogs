class MoreAdminLogsHelper
{
	private bool _isJson;
	private bool _isOverride;
	
	void MoreAdminLogsHelper(bool isJson, bool isOverride)
	{
		_isJson = isJson;
		_isOverride = isOverride;
	}
	
	// Vector3 info
	string Vector3Info(vector vec) {
		if (vec[0] < 0.001 && vec[0] > -0.001) vec[0] = 0;
		if (vec[1] < 0.001 && vec[1] > -0.001) vec[1] = 0;
		if (vec[2] < 0.001 && vec[2] > -0.001) vec[2] = 0;
		string pos = string.Format("%1, %2, %3", vec[0], vec[1], vec[2]);
		if (_isJson) pos = string.Format("{\"x\":%1,\"y\":%2,\"z\":%3}", vec[0], vec[1], vec[2]);
		return pos;
	}

	// Vector4 (Quaternion) info
	string Vector4Info(float vec[4]) {
		if (vec[0] < 0.001 && vec[0] > -0.001) vec[0] = 0;
		if (vec[1] < 0.001 && vec[1] > -0.001) vec[1] = 0;
		if (vec[2] < 0.001 && vec[2] > -0.001) vec[2] = 0;
		if (vec[3] < 0.001 && vec[3] > -0.001) vec[3] = 0;
		string pos = string.Format("%1, %2, %3, %4", vec[0], vec[1], vec[2], vec[3]);
		if (_isJson) pos = string.Format("{\"x\":%1,\"y\":%2,\"z\":%3,\"w\":%3}", vec[0], vec[1], vec[2], vec[3]);
		return pos;
	}

	// Object info
	string ObjectInfo( Object item, bool withParent = false, bool withOwner = false, bool withHp = false )
	{
		if (!item) return "null";
		EntityAI eitem = EntityAI.Cast(item);
		if (eitem) {
			return EntityInfo(eitem, withParent, withOwner, withHp);
		}
		string type = item.GetType();
		
		float percentHealth = (item.GetHealth() * 100) / item.GetMaxHealth();
		string parentInfo = "";
		string ownerInfo = "";
		Object parentObj = NULL;
		if (withParent) {
			parentObj = Object.Cast(item.GetParent());
			if (parentObj) parentInfo = ObjectInfo(parentObj);
		}
		// a bit more complex for objects
		if (withOwner && parentObj && EntityAI.Cast(item)) {
			PlayerBase owner = PlayerBase.Cast(EntityAI.Cast(item).GetHierarchyRootPlayer());
			if (owner) ownerInfo = PlayerInfoShort(owner);
		}
		if (_isJson) {
			string ret = "";
			ret = string.Format("\"id\":\"%1\",\"type\":\"%2\"", item.GetID(), type);
			if (withHp) ret += string.Format(",\"hp100\":%1", percentHealth);
			if (withParent && parentObj) ret += string.Format(",\"parent\":%1", parentInfo);
			if (withOwner && owner) ret += string.Format(",\"owner\":%1", ownerInfo);
			return "{" + ret + "}";
		}
		string base = string.Format("%1::%2", type, item.GetID());
		if (withHp) base = string.Format("%1/%3::%2", type, item.GetID(), percentHealth);
		string parents = "";
		if (withParent && parentObj) parents = parentInfo;
		if (withOwner && owner) {
			if (parents != "") parents += " - ";
			parents += ownerInfo;
		}
		if (parents != "") return base + "{" + parents + "}";
		return base;
	}	
	
	// EntityAI info
	string EntityInfo(EntityAI item, bool withParent = false, bool withOwner = false, bool withHp = false, bool withQuantity = false, bool withPosition = false )
	{
		if (!item) return "null";
		if (item.IsPlayer()) return PlayerInfoShort(PlayerBase.Cast(item));
		ItemBase bitem = ItemBase.Cast(item);
		if (bitem) return this.ItemInfo(bitem, withParent, withOwner, withHp, withQuantity, withPosition);
		string type = item.GetType();
		
		float percentHealth = (item.GetHealth() * 100) / item.GetMaxHealth();
		string parentInfo = "";
		string ownerInfo = "";
		EntityAI parentAi = NULL;
		PlayerBase owner = NULL;
		if (withParent) {
			parentAi = item.GetHierarchyParent();
			if (parentAi) parentInfo = EntityInfo(parentAi);
		}
		if (withOwner) {
			owner = PlayerBase.Cast(item.GetHierarchyRootPlayer());
			if (owner) ownerInfo = PlayerInfoShort(owner);
		}
		if (_isJson) {
			string ret = "";
			ret = string.Format("\"id\":\"%1\",\"type\":\"%2\"", item.GetID(), type);
			if (withHp) ret += string.Format(",\"hp100\":%1", percentHealth);
			if (withParent && parentAi) ret += string.Format(",\"parent\":%1", parentInfo);
			if (withOwner && owner) ret += string.Format(",\"owner\":%1", ownerInfo);
			return "{" + ret + "}";
		}
		string base = string.Format("%1::%2", type, item.GetID());
		if (withHp) base = string.Format("%1/%3::%2", type, item.GetID(), percentHealth);
		string parents = "";
		if (withParent && parentAi) parents = parentInfo;
		if (withOwner && owner) {
			if (parents != "") parents += " - ";
			parents += ownerInfo;
		}
		if (parents != "") return base + "{" + parents + "}";
		return base;
	}
	
	// ItemBase info
	string ItemInfo( ItemBase item, bool withParent = false, bool withOwner = false, bool withHp = false, bool withQuantity = false, bool withPosition = false )
	{
		if (!item) return "null";
		string type = item.GetType();
		float percentHealth = (item.GetHealth() * 100) / item.GetMaxHealth();

		string amount = item.GetQuantity().ToString();
		if (item.HasQuantity() )
		{
			string maxAmount = item.GetQuantityMax().ToString();
			if (_isJson) {
				amount = string.Format("\"quantity\":%1,\"maxq\":%2", amount, maxAmount);
			} else {
				amount = "{" + amount + "/" + maxAmount + "}";
			}
		} else {
			amount = "";
		}
		if (item.IsMagazine()) {
			Magazine mitem = Magazine.Cast(item);
			if (mitem) {
				if (_isJson) {
					amount = string.Format("\"ammo\":%1,\"ammoMax\":%2", mitem.GetAmmoCount(), mitem.GetAmmoMax());
				} else {
					amount = "{" + mitem.GetAmmoCount().ToString() + "}";
				}
			}
		}
		
		string base = "";
		base = string.Format("%1::%2", type, item.GetID());
		if (_isJson) base = string.Format("\"id\":\"%1\",\"type\":\"%2\"", item.GetID(), item.GetType());
		if (withQuantity && amount != "") {
			if (_isJson) { base += "," + amount; }
			else { base = string.Format("%1%2::%3", type, amount, item.GetID()); }
		}
		if (withHp) {
			if (_isJson) { base += string.Format(",\"hp100\":%1", percentHealth) }
			else {
				if (withQuantity) { base = string.Format("%1%3/%2::%4", type, percentHealth, amount, item.GetID()); }
				else { base = string.Format("%1/%2::%3", type, percentHealth, item.GetID()); }
			}
		}
		if (withPosition) {
			string itemPos = Vector3Info( item.GetPosition() );
			if (_isJson) { base += string.Format(",\"pos\":%1", itemPos); }
			else { base += string.Format("{%1}", itemPos); }
		}
		
		EntityAI parent = item.GetHierarchyParent();
		string parentInfo = "";
		if (withParent && parent) {
			parentInfo = EntityInfo(parent);
		}
		
		PlayerBase owner = PlayerBase.Cast(item.GetHierarchyRootPlayer());
		string ownerInfo = "";
		if (withOwner && owner) {
			ownerInfo = PlayerInfoShort(owner);
			if (parent.IsPlayer() && parent.GetID() == owner.GetID()) owner = NULL;
		}

		string parents = "";
		if (withParent && parent) {
			parents = parentInfo;
			if (_isJson) parents = string.Format("\"parent\":%1", parentInfo);
		}
		if (withOwner && owner) {
			if (withParent && parent) {
				if (parent.IsPlayer() && parent.GetID() == owner.GetID()) {
				} else {
					if (_isJson) { parents += string.Format(",\"owner\":%1", ownerInfo); }
					else { parents += " - " + parentInfo; }
				}
			} else {
				if (_isJson) { parents = string.Format("\"owner\":%1", ownerInfo); }
				else { parents = ownerInfo; }
			}
		}
		if (_isJson) {
			if (parents != "") return string.Format("{%1,%2}",base, parents);
			return string.Format("{%1}",base);
		}
		if (parents != "") return string.Format("%1{%2}",base, parents);
		return base;
	}

	// PlayerBase info
	string PlayerInfo( PlayerBase player, bool withStats = false )
	{
		if (!player) return "null";
		return PlayerPrefix( player, !withStats);
	}
	
	// PlayerBase short info
	string PlayerInfoShort( PlayerBase player )
	{
		if (!player) return "null";
		PlayerIdentity identity = player.GetIdentity();
		if (!identity) {
			if (_isJson) return string.Format("{\"id\":\"%1\",\"type\":\"player\"}", player.GetID());
			return string.Format("player::%1", player.GetID());
		}
		if (_isJson) return string.Format("{\"id\":\"%1\",\"name\":\"%2\",\"steamId\":\"%4\",\"dzid\":\"%3\"}", player.GetID(), identity.GetName(), identity.GetId(), identity.GetPlainId());
		return string.Format("{%2}::%1/%3/%4", player.GetID(), identity.GetName(), identity.GetId(), identity.GetPlainId());
	}
	
	// PlayerBase stats
	string PlayerStatsLine( PlayerBase player )
	{
		if (!player) return "null";
		
		bool dead = !player.IsAlive();
		bool inCar = player.IsInVehicle();
		bool inWater = player.IsInWater();
		bool bloodHanded = player.HasBloodyHands();
		
		int bleeds = player.GetBleedingSourceCount();
		float energy = player.GetStatEnergy().Get();
		float water = player.GetStatWater().Get();
		float blood = player.GetHealth("","Blood");
		float hp = player.GetHealth();
		float immunity = player.GetImmunity();
		float heatComfort = player.GetStatHeatComfort().Get();
		float toxicity = player.GetStatToxicity().Get();
		
		string stats = "";
		string stateStats = "";
		
		if (_isJson) {
			stats = string.Format("{\"bleeds\":%1,\"energy\":%2,\"water\":%3,\"heatComfort\":%4,\"blood\":%5,\"health\":%6,\"immunity\":%7,\"toxicity\":%8,", bleeds, energy, water, heatComfort, blood, hp, immunity, toxicity);
			stateStats = string.Format("\"dead\":%4,\"bloodyHands\":%1,\"inCar\":%2,\"inWater\":%3}", bloodHanded, inCar, inWater, dead);
			stats += stateStats;
		} else {
			stats = string.Format("C:%1;E:%2;W:%3;HC:%4;B:%5;H:%6;I:%7;T:%8", bleeds, energy, water, heatComfort, blood, hp, immunity, toxicity);
			stateStats = string.Format("bh:%1;ic:%2;iw:%3", bloodHanded, inCar, inWater);
			stats += ";" + stateStats;
			if (dead) stats = "!DEAD;" + stats;
		}
		if (stats == "") stats = "null";
		return stats;
	}
	
	string PlayerSkelton( PlayerBase player)
	{
		if (!player) return "null";

		vector heading = MiscGameplayFunctions.GetHeadingVector(player);
		string body = Vector3Info(heading);

		// string body = Vector3Info(player.GetDirection());
		string head = "null";
		string neck = "null";
		string spine1 = "null";
		string spine2 = "null";
		string spine3 = "null";
		
		// bones
		vector transform = "0 0 0";

		int boneIdx = player.GetBoneIndexByName("Head");
		player.GetBoneTransformWS( boneIdx, transform );
		head = Vector3Info( transform );

		boneIdx = player.GetBoneIndexByName("Neck");
		player.GetBoneTransformWS( boneIdx, transform );
		neck = Vector3Info( transform );

		boneIdx = player.GetBoneIndexByName("spine1");
		player.GetBoneTransformWS( boneIdx, transform );
		spine1 = Vector3Info( transform );

		boneIdx = player.GetBoneIndexByName("spine2");
		player.GetBoneTransformWS( boneIdx, transform );
		spine2 = Vector3Info( transform );

		boneIdx = player.GetBoneIndexByName("spine3");
		player.GetBoneTransformWS( boneIdx, transform );
		spine3 = Vector3Info( transform );

		if (_isJson) {
			return string.Format("{\"body\":%1,\"head\":%2,\"neck\":%3,\"spine1\":%4,\"spine2\":%5,\"spine3\":%6}", body, head, neck, spine1, spine2, spine3);
		}
		return string.Format("body=<%1> head=<%2> neck=<%3> spine1=<%4> spine2=<%5> spine3=<%6>", body, head, neck, spine1, spine2, spine3);
	}
	
	string PlayerPrefix( PlayerBase player, bool noStats = false )
	{	
		if (!player) return "null";
		
		string sid = player.GetID().ToString();
		string name = "null";
		string pid = "null";
		string steamId = "null";
		if ( !player.IsAlive() && _isJson ) name = name + " !DEAD";
		
		string stats = PlayerStatsLine(player);
		string pos = Vector3Info(player.GetPosition());
		vector heading = MiscGameplayFunctions.GetHeadingVector(player);
		string body = Vector3Info(heading);
		// string body = Vector3Info(player.GetDirection());
		//string skeleton = PlayerSkelton(player);

		PlayerIdentity pIdentity = player.GetIdentity();
		
		if ( !pIdentity ) {
			if (_isJson) {
				if (noStats) {
					return string.Format("{\"id\":\"%1\",\"name\":\"%2\",\"dzid\":null,\"steamId\":null,\"position\":%3}", sid, name, pos);
				}
				return string.Format("{\"id\":\"%1\",\"name\":\"%2\",\"dzid\":null,\"steamId\":null,\"stats\":%3,\"position\":%4}", sid, name, stats, pos);
			}
			if (noStats) {
				return string.Format("id=<%1> name=<%2> dzid=<%3> steam=<%4> pos=<%5>", sid, name, pid, steamId, pos);
			}
			return string.Format("id=<%1> name=<%2> dzid=<%3> steam=<%4> stats=<%5> pos=<%6>", sid, name, pid, steamId, stats, pos);
		}
		
		name = pIdentity.GetName();
		pid = pIdentity.GetId();
		steamId = pIdentity.GetPlainId();
		
		if (_isJson) {
			if (noStats) {
				if (!player.IsAlive()) return string.Format("{\"id\":\"%1\",\"name\":\"%2\",\"dzid\":\"%3\",\"steamId\":\"%4\",\"position\":%5,\"direction\":%6,\"dead\":true}", sid, name, pid, steamId, pos, body);
				return string.Format("{\"id\":\"%1\",\"name\":\"%2\",\"dzid\":\"%3\",\"steamId\":\"%4\",\"position\":%5,\"direction\":%6}", sid, name, pid, steamId, pos, body);
			}
			if (!player.IsAlive()) return string.Format("{\"id\":\"%1\",\"name\":\"%2\",\"dzid\":\"%3\",\"steamId\":\"%4\",\"position\":%5,\"direction\":%6,\"stats\":%7,\"dead\":true}", sid, name, pid, steamId, pos, body, stats);
			return string.Format("{\"id\":\"%1\",\"name\":\"%2\",\"dzid\":\"%3\",\"steamId\":\"%4\",\"position\":%5,\"direction\":%6,\"stats\":%7}", sid, name, pid, steamId, pos, body, stats);
		}
		
		if ( !player.IsAlive() ) name = name + " !DEAD";
		
		if (noStats) {
			return string.Format("id=<%1> name=<%2> dzid=<%3> steamId=<%4> pos=<%5> direction=<%6>", sid, name, pid, steamId, pos, body);
		}
		return string.Format("id=<%1> name=<%2> dzid=<%3> steamId=<%4> pos=<%5> direction=<%6> stats=<%7>", sid, name, pid, steamId, pos, body, stats);
	}

	// ActionBase info
	string ActionInfo(ActionBase action, ActionData action_data)
	{
		string actionId = action.GetID().ToString();
		string actionName = action.GetText();
		Object target = NULL;
		ItemBase item = NULL;
		string targetInfo = "null";
		string itemInfo = "null";
		string message = "";
		string partInfo = "";
		
		if (action_data.m_Target) {
			target = action_data.m_Target.GetObject();
			if (action.IsUsingProxies()) target = action_data.m_Target.GetParent();
		}
		if (action_data.m_MainItem) {
			item = action_data.m_MainItem;
		}

		if (target) targetInfo = ObjectInfo(target);
		if (item) itemInfo = ItemInfo(item);
		BuildPartActionData bpActionData = BuildPartActionData.Cast(action_data);
		if (bpActionData) partInfo = bpActionData.m_PartType;
		if ( target && target.CanUseConstruction() ) partInfo = target.GetActionComponentName( action_data.m_Target.GetComponentIndex() );

		if (item && target && targetInfo != "null") {
			message = string.Format("id=<%1> name=<%2> target=<%4> item=<%3>", actionId, actionName, itemInfo, targetInfo);
			if (_isJson) message = string.Format("\"id\":\"%1\",\"name\":\"%2\",\"target\":%4,\"item\":%3", actionId, actionName, itemInfo, targetInfo);
		}
		if (item && !target) {
			message = string.Format("id=<%1> name=<%2> item=<%3>", actionId, actionName, itemInfo);
			if (_isJson) message = string.Format("\"id\":\"%1\",\"name\":\"%2\",\"item\":%3", actionId, actionName, itemInfo);
		}
		if (!item && target) {
			message = string.Format("id=<%1> name=<%2> target=<%3>", actionId, actionName, targetInfo);
			if (_isJson) message = string.Format("\"id\":\"%1\",\"name\":\"%2\",\"target\":%3", actionId, actionName, targetInfo);
		}
		if (!item && !target) {
			message = string.Format("id=<%1> name=<%2>", actionId, actionName);
			if (_isJson) message = string.Format("\"id\":\"%1\",\"name\":\"%2\"", actionId, actionName);
		}
		if (partInfo != "") {
			if (_isJson) { message += string.Format(",\"part\":\"%1\"", partInfo); }
			else { message += " part=<"+partInfo+">"; }
		}
		if (_isJson) return "{"+message+"}";
		return message;
	}

}