using UnityEngine;

[DisallowMultipleComponent]
public sealed class CheckpointBehaviour : MonoBehaviour
{
    #region Parameters
    [SerializeField] private TagProvider tagProvider = null;
    [SerializeField] private MeshRenderer mesh = null;

    private Color checkpointColor;
    #endregion

    #region MonoBehaviour API
    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag(tagProvider.PlayerTag) && other.gameObject.TryGetComponent(out MeshRenderer meshRenderer))
        {
            meshRenderer.material.color = checkpointColor;
        }
    }
    #endregion

    #region Custom methods
    public void ChangeCheckpointColor(Color color)
    {
        checkpointColor = color;
        mesh.material.color = color;
    }
    #endregion
}
