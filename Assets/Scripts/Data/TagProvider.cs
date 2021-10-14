using UnityEngine;

[CreateAssetMenu(fileName = "TagProvider", menuName = "Scriptable Objects/Tag Provider", order = 1)]
public sealed class TagProvider : ScriptableObject
{
    [SerializeField] private string playerTag = "Player";
    [SerializeField] private string checkpointTag = "Checkpoint";
    [SerializeField] private string obstacleTag = "Obstacle";
    [SerializeField] private string foodTag = "Food";
    [SerializeField] private string crystalTag = "Crystal";

    public string PlayerTag => playerTag;
    public string CheckpointTag => checkpointTag;
    public string ObstacleTag => obstacleTag;
    public string FoodTag => foodTag;
    public string CrystalTag => crystalTag;
}
